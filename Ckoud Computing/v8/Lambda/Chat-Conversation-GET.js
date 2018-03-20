'use strict';

var AWS = require('aws-sdk');

var dynamo = new AWS.DynamoDB();

exports.handler = function (event, context, callback) {
    dynamo.query({
        TableName: 'Chat-Conversations',
        IndexName: 'Username-ConversationId-index',
        Select: 'ALL_PROJECTED_ATTRIBUTES',
        KeyConditionExpression: 'Username = :username',
        ExpressionAttributeValues: {':username': {S: 'Student'}}
    }, function (err, data) {
        handleIdQuery(err, data, callback, [], 'Student');
    });
};

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

function finished(convos) {
    for (var i = 0; i < convos.length; i++) {
        if (!convos[i].participants) {
            return false;
        }
    }
    return true;
}

function loadDetails(ids, callback) {
    console.log("Loading details");
    var convos = [];
    ids.forEach(function (id) {
        var convo = {id: id};
        convos.push(convo);
    });

    if(convos.length > 0) {
        convos.forEach(function (convo) {
            loadConvoLast(convo, convos, callback);
        });
    } else {
        callback(null, convos);
    }
}

function loadConvoLast(convo, convos, callback) {
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
            loadConvoParticipants(convo, convos, callback);
        } else {
            callback(err);
        }
    });
}

function loadConvoParticipants(convo, convos, callback) {
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

            if (finished(convos)) {
                callback(null, convos);
            }
        } else {
            callback(err);
        }
    });
}