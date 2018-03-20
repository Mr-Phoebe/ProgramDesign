'use strict';

var AWS = require('aws-sdk');

var S3 = new AWS.S3();

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
        S3.getObject({
            Bucket: bucket,
            Key: 'data/conversations/' + id + '.json'
        }, function (err, data) {
            done(err, err ? null : JSON.parse(data.Body.toString()));
        });
    } else {
        done('No cases hit');
    }
};