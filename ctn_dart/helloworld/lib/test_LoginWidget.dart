import 'package:flutter/material.dart';


class InitWidget extends StatefulWidget {
  InitWidget({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _LoginState createState() => new _LoginState();
}

class _LoginState extends State<InitWidget> {
  String mUserName = "";
  String mPassword = "";
  bool mIsLoggedIn = false;

  void _RequestToLogin() {
    setState(() {
      this.mUserName = "My User Name";
      this.mPassword = "My Password";
      this.mIsLoggedIn=true;
    });
  }

  @override
  Widget build(BuildContext context) {
    if(!this.mIsLoggedIn){
      return new Scaffold(
        body : new Center(
          child: new Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              new TextField(// Text field for User Name
                decoration: new InputDecoration(
                  hintText: 'User Name',
                ),
              ),
              new TextField(// Text field for Password
                decoration: new InputDecoration(
                  hintText: 'Password',
                ),
                obscureText: true,
              ),
              new FlatButton(
                child: new Text("OK"),
                onPressed: _RequestToLogin, // null disables the button
              ),
            ],
          ),
        ),
      );
    }
  else{
      return new Scaffold(
        body : new Center(
          child: new Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              new Text(this.mUserName),
              new Text(this.mPassword),
            ],
          ),
        ),
      );
    }
  }
}