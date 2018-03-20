'use strict';

var AWS = require('aws-sdk');

var dynamo = new AWS.DynamoDB();

exports.handler = function (event, context, callback) {

    const done = function (err, res) {
        callback(null, {
            statusCode: err ? '400' : '200',
            body: err ? JSON.stringify(err) : JSON.stringify(res),
            headers: {
                'Content-Type': 'application/json',
                'Access-Control-Allow-Origin': 'http://hw-chatroom.s3-website-us-east-1.amazonaws.com'
            }
        });
    };

    var path = event.pathParameters.proxy;

    if (path === 'conversations') {
        dynamo.query({
            TableName: 'Chat-Conversations',
            IndexName: 'Username-ConversationId-index',
            Select: 'ALL_PROJECTED_ATTRIBUTES',
            KeyConditionExpression: 'Username = :username',
            ExpressionAttributeValues: {':username': {S: 'Student'}}
        }, function (err, data) {
            handleIdQuery(err, data, done, [], 'Student');
        });
    } else if (path.startsWith('conversations/')) {
        var id = path.substring('conversations/'.length);
        dynamo.query({
            TableName: 'Chat-Messages',
            ProjectionExpression: '#T, Sender, Message',
            ExpressionAttributeNames: {'#T': 'Timestamp'},
            KeyConditionExpression: 'ConversationId = :id',
            ExpressionAttributeValues: {':id': {S: id}}
        }, function (err, data) {
            loadMessages(err, data, id, [], done);
        });
    } else {
        done('No cases hit');
    }
};

function loadMessages(err, data, id, messages, callback) {
    if (err === null) {
        data.Items.forEach(function (message) {
            messages.push({
                sender: message.Sender.S,
                time: Number(message.Timestamp.N),
                message: message.Message.S
            });
        });
        if(data.LastEvaluatedKey) {
            dynamo.query({
                TableName: 'Chat-Messages',
                ProjectionExpression: '#T, Sender, Message',
                KeyConditionExpression: 'ConversationId = :id',
                ExpressionAttributeNames: {'#T': 'Timestamp'},
                ExpressionAttributeValues: {':id': {S: id}},
                ExclusiveStartKey: data.LastEvaluatedKey
            }, function (err, data) {
                loadMessages(err, data, id, messages, callback);
            });
        } else {
            loadConversationDetail(id, messages, callback);
        }
    } else {
        callback(err);
    }
}

function loadConversationDetail(id, messages, callback) {
    dynamo.query({
        TableName: 'Chat-Conversations',
        Select: 'ALL_ATTRIBUTES',
        KeyConditionExpression: 'ConversationId = :id',
        ExpressionAttributeValues: {':id': {S: id}}
    }, function (err, data) {
        if (err === null) {
            var participants = [];
            data.Items.forEach(function (item) {
                participants.push(item.Username.S);
            });

            callback(null, {
                id: id,
                participants: participants,
                last: messages.length > 0 ? messages[messages.length-1].time : undefined,
                messages: messages
            });
        } else {
            callback(err);
        }
    });
}

function handleIdQuery(err, data, callback, ids, username) {
    console.log("Username query results: " + JSON.stringify(data));
    if (err === null) {
        data.Items.forEach(function (item) {
            ids.push(item.ConversationId.S);
        });

        if (data.LastEvaluatedKey) {
            dynamo.query({
                TableName: 'Chat-Conversations',
                IndexName: 'Username-ConversationId-index',
                Select: 'ALL_PROJECTED_ATTRIBUTES',
                KeyConditionExpression: 'Username = :username',
                ExpressionAttributeValues: {':username': {S: username}},
                ExclusiveStartKey: data.LastEvaluatedKey
            }, function (err, data) {
                handleIdQuery(err, data, callback, ids, username);
            });
        } else {
            loadDetails(ids, callback);
        }
    } else {
        callback(err);
    }
}

function loadDetails(ids, callback) {
    console.log("Loading details");
    var convos = [];
    ids.forEach(function (id) {
        var convo = {id: id};
        convos.push(convo);
    });

    if(convos.length > 0) {
        var number = [0];
        convos.forEach(function (convo) {
            loadConvoLast(convo, convos, number, callback);
        });
    } else {
        callback(null, convos);
    }
}

function loadConvoLast(convo, convos, number, callback) {
    dynamo.query({
        TableName: 'Chat-Messages',
        ProjectionExpression: '#T',
        Limit: 1,
        ScanIndexForward: false,
        KeyConditionExpression: 'ConversationId = :id',
        ExpressionAttributeNames: {'#T': 'Timestamp'},
        ExpressionAttributeValues: {':id': {S: convo.id}}
    }, function (err, data) {
        if (err === null) {
            if (data.Items.length === 1) {
                convo.last = Number(data.Items[0].Timestamp.N);
            }
            loadConvoParticipants(convo, convos, number, callback);
        } else {
            callback(err);
        }
    });
}

function loadConvoParticipants(convo, convos, number, callback) {
    dynamo.query({
        TableName: 'Chat-Conversations',
        Select: 'ALL_ATTRIBUTES',
        KeyConditionExpression: 'ConversationId = :id',
        ExpressionAttributeValues: {':id': {S: convo.id}}
    }, function (err, data) {
        if (err === null) {
            var participants = [];
            data.Items.forEach(function (item) {
                participants.push(item.Username.S);
            });
            convo.participants = participants;
            number[0] += 1;
            if (convos.length == number[0]) {
                callback(null, convos);
            }
        } else {
            callback(err);
        }
    });
}