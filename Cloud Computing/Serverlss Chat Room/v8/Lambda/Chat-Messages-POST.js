'use strict';

var AWS = require('aws-sdk');

var dynamo = new AWS.DynamoDB();

exports.handler = function (event, context, callback) {
    dynamo.query({
        TableName: 'Chat-Messages',
        ProjectionExpression: 'Sender',
        KeyConditionExpression: 'ConversationId = :id',
        ExpressionAttributeValues: {':id': {S: event.id}}
    }, function (err, data) {
        loadMessages(err, data, event, callback);
    });
};

function loadMessages(err, data, event, callback) {
    if (err === null) { 
        var other = "";
        data.Items.forEach(function (message) {
            if (message.Sender.S != "Student") {
                other = message.Sender.S;
            }
        });
        postMessages(err, event, other, callback);
    } else {
        callback(err);
    }
}

function postMessages(err, event, othername, callback) {
    if (err === null) {
        dynamo.putItem({
            TableName: 'Chat-Messages',
            Item: {
                ConversationId: {S: event.id},
                Timestamp: {
                    N: "" + new Date().getTime()
                },
                Message: {S: event.message},
                Sender: {S: 'Student'}
            }
        }, function(err) {
            if(err !== null) {
                callback(err);
            } else {
                callback(null, null);
            }
        });
    } else {
        callback(err);
    }
}