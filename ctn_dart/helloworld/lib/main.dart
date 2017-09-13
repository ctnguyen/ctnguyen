import 'package:flutter/material.dart';


import 'helloworld_lib.dart';
import 'test_LoginWidget.dart';
import 'dart:io';

/*
void main() {
  //runApp(new TestHelloWorldApp());

  runApp(new MaterialApp(
      title: 'Flutter Tutorial',
      home: new InitWidget()
  ));

  //runApp(new Center(child: new Text('Hello, world!')));
}
*/

// Example of websocket
// Launch the phone emulator (tested on Android)
// Run the example from boost::beast : ./websocket-server-sync 0.0.0.0 9090
// Put the break point in the websocket_server_sync.cpp in funtion do_session to see if it connect
// Run the project dart here.
main() async {
  var socket = await WebSocket.connect('ws://10.0.2.2:9090');
  socket.add('Hello, World!');
}