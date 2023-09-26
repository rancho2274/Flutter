import 'package:flutter/material.dart';

class details extends StatelessWidget {
  const details({Key? key, this.name, this.mail, this.mob}) : super(key: key);
  final String? name;
  final String? mail;
  final String? mob;
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SafeArea(
        child: Column(
          children: <Widget>[
            Text(
              'Name: '+ name.toString(),
          style: const TextStyle(
          fontWeight: FontWeight.bold,
          fontSize: 30.0,
            )
            ),
            Text(
              'Mail ID: '+ mail.toString(),
              style: const TextStyle(
                fontWeight: FontWeight.bold,
                fontSize: 30.0,
            )
            ),
            Text(
                'Mobile Number: '+ mob.toString(),
                style: const TextStyle(
                  fontWeight: FontWeight.bold,
                  fontSize: 30.0,
                )
            ),

          ],
        ),
      ),
    );
  }
}
