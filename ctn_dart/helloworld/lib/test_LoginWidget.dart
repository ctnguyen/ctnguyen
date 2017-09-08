import 'package:flutter/material.dart';

class LoginWidgetApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Currency Swap',
      theme: new ThemeData(primarySwatch: Colors.blue,),
      home: new LoginWidget(title: 'Login'),
    );
  }
}

class LoginWidget extends StatefulWidget {
  LoginWidget({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _LoginState createState() => new _LoginState();
}

class _LoginState extends State<LoginWidget> {
  String username = "username";
  String password = "password";

  @override
  Widget build(BuildContext context) {
    return new Center(
      child: new Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: <Widget>[
          new Text(this.username,),
          new Text(this.password,),
          ],
        ),
      );
  }
}