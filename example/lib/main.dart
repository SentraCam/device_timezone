import 'dart:async';

import 'package:flutter/material.dart';
import 'package:device_timezone/device_timezone.dart';

void main() => runApp(const MyApp());

class MyApp extends StatefulWidget {

  const MyApp({super.key});
  @override
  MyAppState createState() => MyAppState();
}

class MyAppState extends State<MyApp> {
  String? _timezone = 'Unknown';
  List<String> _availableTimezones = <String>[];

  @override
  void initState() {
    super.initState();
    _initData();
  }

  Future<void> _initData() async {
    try {
      _timezone = await DeviceTimezone.getLocalTimezone();
    } catch (e) {
      debugPrint('Could not get the local timezone');
    }
    try {
      _availableTimezones = await DeviceTimezone.getAvailableTimezones();
      _availableTimezones.sort();
    } catch (e) {
      debugPrint('Could not get available timezones');
    }
    if (mounted) {
      setState(() {});
    }
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Local timezone app'),
        ),
        body: Column(
          children: <Widget>[
            Text('Local timezone: $_timezone\n'),
            const Text('Available timezones:'),
            Expanded(
              child: ListView.builder(
                itemCount: _availableTimezones.length,
                itemBuilder: (_, index) => Text(_availableTimezones[index]),
              ),
            )
          ],
        ),
      ),
    );
  }
}
