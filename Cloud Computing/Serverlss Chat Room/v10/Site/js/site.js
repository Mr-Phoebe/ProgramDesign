var ChatApp = window.ChatApp || {};

(function scopeWrapper($) {

    var currentUsername = 'Student';

    var lastChat = null;

    var apiClient = apigClientFactory.newClient();

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

}(jQuery));