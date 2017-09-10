import 'package:flutter/material.dart';


import 'helloworld_lib.dart';
import 'test_LoginWidget.dart';

void main() {
  //runApp(new TestHelloWorldApp());
  runApp(new MaterialApp(
      title: 'Flutter Tutorial',
      home: new InitWidget()
  ));
  //runApp(new Center(child: new Text('Hello, world!')));
}