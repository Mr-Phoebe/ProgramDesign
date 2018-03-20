var ChatApp = window.ChatApp || {};

(function scopeWrapper($) {

    var userPool = new AmazonCognitoIdentity.CognitoUserPool(poolData);

    var currentUsername = 'Student';

    var lastChat = null;

    var apiClient = apigClientFactory.newClient();

    ChatApp.checkLogin = function (redirectOnRec, redirectOnUnrec) {
        var cognitoUser = userPool.getCurrentUser();
        if (cognitoUser !== null) {
            if (redirectOnRec) {
                window.location = '/chats.html';
            }
        } else {
            if (redirectOnUnrec) {
                window.location = '/';
            }
        }
    };

    ChatApp.login = function () {
        var username = $('#username').val();
        var authenticationData = {
            Username: username,
            Password: $('#password').val()
        };

        var authenticationDetails = new AmazonCognitoIdentity.AuthenticationDetails(authenticationData);
        var userData = {
            Username: username,
            Pool: userPool
        };
        var cognitoUser = new AmazonCognitoIdentity.CognitoUser(userData);
        cognitoUser.authenticateUser(authenticationDetails, {
            onSuccess: function () {
                window.location = '/chats.html';
            },
            onFailure: function (err) {
                alert(err);
            }
        });
    };

    ChatApp.logout = function () {
        var cognitoUser = userPool.getCurrentUser();
        cognitoUser.signOut();
        window.location = '/';
    };

    ChatApp.populateChats = function () {
        apiClient.conversationsGet({}, null, {})
            .then(function (result) {

                result.data.forEach(function (convo) {
                    var otherUsers = [];
                    convo.participants.forEach(function (user) {
                        if (user !== currentUsername) {
                            otherUsers.push(user);
                        }
                    });

                    var last = '&nbsp;';
                    if (convo.last) {
                        last = moment(new Date(convo.last)).fromNow();
                    }

                    $('TBODY').append('<tr><td><a href="chat.html#' + convo.id + '">' + otherUsers.join(', ') + '</a></td><td>' + last + '</td></tr>');
                });
                $('TBODY').append('<tr><td></td><td></td></tr>');
            });
    };

    ChatApp.loadChat = function () {
        apiClient.conversationsIdGet({id: location.hash.substring(1)}, null, {})
            .then(function (result) {
                var lastRendered = lastChat === null ? 0 : lastChat;
                if((lastChat === null && result.data.last) || lastChat < result.data.last) {
                    lastChat = result.data.last;
                } else {
                    return;
                }
                result.data.messages.forEach(function (message) {
                    if(message.time > lastRendered) {
                        var panel = $('<div class="panel">');
                        if (message.sender === currentUsername) {
                            panel.addClass('panel-default');
                        } else {
                            panel.addClass('panel-info');
                            panel.append('<div class="panel-heading">' + message.sender + '</div>');
                        }
                        var body = $('<div class="panel-body">').text(message.message);
                        panel.append(body);
                        panel.append('<div class="panel-footer messageTime" data-time="' + message.time + '">' + moment(message.time).fromNow() + '</div>');

                        var row = $('<div class="row">');
                        var buffer = $('<div class="col-xs-4">');
                        var holder = $('<div class="col-xs-8">');
                        holder.append(panel);

                        if (message.sender === currentUsername) {
                            row.append(buffer);
                            row.append(holder);
                        } else {
                            row.append(holder);
                            row.append(buffer);
                        }

                        $('#chat').append(row);
                    }
                });
                window.scrollTo(0, document.body.scrollHeight);
            });
    };

    ChatApp.send = function () {
        apiClient.conversationsIdPost({id: location.hash.substring(1)}, $('#message').val(), {})
            .then(function () {
                $('#message').val('').focus();
                ChatApp.loadChat();
            });

    };

    ChatApp.populatePeople = function () {
        apiClient.usersGet({}, null, {})
            .then(function (result) {
                result.data.forEach(function (name) {
                    var button = $('<button class="btn btn-primary">Start Chat</button>');
                    button.on('click', function() {
                        ChatApp.startChat(name);
                    });

                    var row = $('<tr>');
                    row.append('<td>' + name + '</td>');
                    var cell = $('<td>');
                    cell.append(button);
                    row.append(cell);
                    $('TBODY').append(row);
                });
                $('TBODY').append('<tr><td></td><td></td></tr>');
            });
    };

    ChatApp.startChat = function (name) {
        apiClient.conversationsPost({}, [name], {})
            .then(function (result) {
                window.location = '/chat.html#' + result.data;
            });
    };

    ChatApp.signup = function () {
        var username = $('#username').val();
        var password = $('#password').val();
        var email = new AmazonCognitoIdentity.CognitoUserAttribute({
            Name: 'email',
            Value: $('#email').val()
        });

        userPool.signUp(username, password, [email], null, function (err, result) {
            if (err) {
                alert(err);
            } else {
                window.location = '/confirm.html#' + username;
            }
        });
    };

    ChatApp.confirm = function () {
        var username = location.hash.substring(1);
        var cognitoUser = new AmazonCognitoIdentity.CognitoUser({
            Username: username,
            Pool: userPool
        });
        cognitoUser.confirmRegistration($('#code').val(), true, function (err, results) {
            if (err) {
                alert(err);
            } else {
                window.location = '/';
            }
        });
    };

    ChatApp.resend = function () {
        var username = location.hash.substring(1);
        var cognitoUser = new AmazonCognitoIdentity.CognitoUser({
            Username: username,
            Pool: userPool
        });
        cognitoUser.resendConfirmationCode(function (err) {
            if (err) {
                alert(err);
            }
        })
    };

}(jQuery));