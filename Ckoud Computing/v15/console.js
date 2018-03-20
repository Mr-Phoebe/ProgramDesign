var userPool = new AmazonCognitoIdentity.CognitoUserPool(poolData);
userPool.getCurrentUser().getSession(function(err, session) { console.log(session.getIdToken().getJwtToken()); })