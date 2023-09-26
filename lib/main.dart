import 'package:flutter/material.dart';
// import 'package:form_field_validator/form_field_validator.dart';
import 'package:flutter/foundation.dart';
import 'yourdetails.dart';

void main() => runApp(MaterialApp(
  debugShowCheckedModeBanner: false,
  initialRoute: '/',
  routes: {'/': (context) => Register()},
));
class Register extends StatefulWidget {
  const Register({Key? key}) : super(key: key);

  @override
  State<Register> createState() => _RegisterState();
}

class _RegisterState extends State<Register> {
  Map userData = {};
  final _formkey = GlobalKey<FormState>();
  final nameTxtCnt =TextEditingController();
  final mobTxtCnt =TextEditingController();
  final mailTxtCnt =TextEditingController();
  void nextpage(BuildContext ctx) {
    Navigator.of(ctx).push(MaterialPageRoute(builder: (_) {
      return details(name: nameTxtCnt.text, mail: mailTxtCnt.text, mob: mobTxtCnt.text);
    }));
  }
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text('Registeration Form'),
        ),
        body: SingleChildScrollView(
          child: Padding(
            padding: const EdgeInsets.all(12.0),
            child: Form(
                key: _formkey,
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: <Widget>[
                    Padding(
                      padding: const EdgeInsets.only(top: 20.0),
                      child: Center(
                        child: Container(
                          width: 200,
                          height: 150,
                          //decoration: BoxDecoration(
                          //borderRadius: BorderRadius.circular(40),
                          //border: Border.all(color: Colors.blueGrey)),
                          child: Image.asset('assets/photo.jpeg'),
                        ),
                      ),
                    ),
                    Padding(
                      padding: const EdgeInsets.all(12.0),
                      child: TextFormField(controller: nameTxtCnt,
                        // validator: ((value) {
                        // if (value == null || value.isEmpty) {
                        // 	 return 'please enter some text';
                        // } else if (value.length < 5) {
                        // 	 return 'Enter atleast 5 Charecter';
                        // }
                        // return null;
                        // }),
                        // validator: MultiValidator([
                        //   RequiredValidator(errorText: 'Enter first named'),
                        //   MinLengthValidator(3,
                        //       errorText: 'Minimum 3 charecter filled name'),
                        // ]),

                        decoration: InputDecoration(
                            hintText: 'Enter you Name',
                            labelText: 'Name',
                            prefixIcon: Icon(
                              Icons.person,
                              color: Colors.green,
                            ),
                            errorStyle: TextStyle(fontSize: 18.0),
                            border: OutlineInputBorder(
                                borderSide: BorderSide(color: Colors.red),
                                borderRadius:
                                BorderRadius.all(Radius.circular(9.0)))),
                      ),
                    ),
                    // Padding(
                    //   padding: const EdgeInsets.all(8.0),
                    //   child: TextFormField(
                    //     // validator: MultiValidator([
                    //     //   RequiredValidator(errorText: 'Enter last named'),
                    //     //   MinLengthValidator(3,
                    //     //       errorText:
                    //     //       'Last name should be atleast 3 charater'),
                    //     // ]),
                    //     decoration: InputDecoration(
                    //         hintText: 'Enter last Name',
                    //         labelText: 'Last name',
                    //         prefixIcon: Icon(
                    //           Icons.person,
                    //           color: Colors.grey,
                    //         ),
                    //         errorStyle: TextStyle(fontSize: 18.0),
                    //         border: OutlineInputBorder(
                    //             borderSide: BorderSide(color: Colors.red),
                    //             borderRadius:
                    //             BorderRadius.all(Radius.circular(9.0)))),
                    //   ),
                    // ),
                    Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: TextFormField(controller: mailTxtCnt,
                        // validator: MultiValidator([
                        //   RequiredValidator(errorText: 'Enter email address'),
                        //   EmailValidator(
                        //       errorText: 'Please correct email filled'),
                        // ]),
                        decoration: InputDecoration(
                            hintText: 'Email',
                            labelText: 'Email',
                            prefixIcon: Icon(
                              Icons.email,
                              color: Colors.lightBlue,
                            ),
                            errorStyle: TextStyle(fontSize: 18.0),
                            border: OutlineInputBorder(
                                borderSide: BorderSide(color: Colors.red),
                                borderRadius:
                                BorderRadius.all(Radius.circular(9.0)))),
                      ),
                    ),
                    Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: TextFormField(controller: mobTxtCnt,
                        // validator: MultiValidator([
                        //   RequiredValidator(errorText: 'Enter mobile number'),
                        //   PatternValidator(r'(^[0,9]{10}$)',
                        //       errorText: 'enter valid mobile number'),
                        // ]),
                        decoration: InputDecoration(
                            hintText: 'Mobile',
                            labelText: 'Mobile',
                            prefixIcon: Icon(
                              Icons.phone,
                              color: Colors.grey,
                            ),
                            border: OutlineInputBorder(
                                borderSide: BorderSide(color: Colors.red),
                                borderRadius:
                                BorderRadius.all(Radius.circular(9)))),
                      ),
                    ),
                    Center(
                        child: Padding(
                          padding: const EdgeInsets.all(18.0),
                          child: Container(
                            // margin: EdgeInsets.fromLTRB(200, 20, 50, 0),
                            child: ElevatedButton(
                              child: Text(
                                'Register',
                                style: TextStyle(color: Colors.white, fontSize: 22),
                              ),
                              onPressed: () {
                                nextpage(context);
                              },
                              // shape: RoundedRectangleBorder(
                              //     borderRadius: BorderRadius.circular(30)),
                              // color: Colors.blue,
                            ),

                            width: MediaQuery.of(context).size.width,

                            height: 50,
                          ),
                        )),


                  ],
                )),
          ),
        ));
  }
}


