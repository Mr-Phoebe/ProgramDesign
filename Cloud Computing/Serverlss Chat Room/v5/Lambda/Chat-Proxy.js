'use strict';

var AWS = require('aws-sdk');

var S3 = new AWS.S3();
var dynamo = new AWS.DynamoDB();

var bucket = 'hw-chatroom';

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
        S3.getObject({
            Bucket: bucket,
            Key: 'data/conversations.json'
        }, function (err, data) {
            done(err, err ? null : JSON.parse(data.Body.toString()));
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
        ExpressionAttributeValues: {
            ':id': {S: id}
        }
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