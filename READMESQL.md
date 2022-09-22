T4C MYSQL ODBC How-To


Episode I: Installing mandatory programs.

1. You will need to get Mysql and an ODBC Connector.
Links: Mysql and ODBC
2. Download the attached t4c.sql to c:/

3. Install Mysql, remember to select the option to add it to the PATH when asked.
4. Install ODBC.
5. Did you install them both? if not, go back to number 3.
6. Open your Start Menu, select execute and write cmd in it ( open up a dos box )
7. Once you have a dos box open, type the following.

--> mysql -u root -p

-it will now ask the password you created upon installing Mysql.
NOTE: If you didn’t create a password, remove the -p switch.

Once you are logged in, you will need to create the database.

--> Create database t4c;
--> Grant all privileges on t4c.* to yourdesiredname@localhost identified by 'yourdesiredpassword';

Remember to put the semicolon in the end ;)
Now we proceed with selecting the newly created db.

--> Use t4c;

All set, now we have to insert some info to the database.

--> source c:/t4c.sql;

NOTE: You need to change the location of the source file according to where you have placed it ;)

It will now add all the tables and other stuff into the mysql database, discard any possible warnings, no actual errors should arise.

If all went well, you should now have a valid database to run your T4C Server off. Next you need to setup the ODBC driver.


Episode II: The Infamous ODBC Setup.


1. Open up your ODBC control panel, this is easiest to achieve by going to start menu, select execute and copy & paste the following in it
--> %SystemRoot%\system32\odbcad32.exe

NOTE: You can also access your ODBC consol via Control Panel-->Administration Tools-->ODBC

2. Select the User DSN tab
3. Click Add
4. Select the newly installed MySQL ODBC 3.51 driver from the list
5. It now ask various information:

-Data Source Name = t4c server
-Description . . . . . = not needed
-Server . . . . . . . . = not needed or localhost
-User . . . . . . . . . . = yourdesiredname (Created in Episode I, without the @localhost)
-Password . . . . . . = yourdesiredpassword (Created in Episode I

6. Select the newly created database from the dropdown list.
7. Click the TEST button to test the connection. It will either say Ok or possibly give you an error if the password/username is wrong.

NOTE: With some ( not all ) Windows XP installations that has SP2 installed the application will hang at this point. This is unfortunate but can be fixed easily by going to start menu, select execute and type
--> netsh winsock reset
Reboot and return to number 1.

Now the ODBC should be ready for use. In the next Episode, we will see how to setup the server itself to use the MySQL ODBC driver.


Episode III: The server setup.


1. Open your T4C Server console (T4CSetup.cpl )located in the server folder
2. Select Authentication tab
- Make sure the ODBC is selected instead of the Radius.

3. At the bottom of the screen you see the ODBC Authentification box, this is where we will need to put some information:

- Data Source Name = t4c server ( Created in Episode II )
- Database Logging Account = yourdesiredname ( Created in Episode I, without the @localhost)
- Database Password = yourdesiredpassword ( Created in Episode I )
- Table = T4CUsers
- Account Name Field = Account
- Password Field = Password

The Time Credits and Where Statement fields can be left blank.

4. All set? Then move on to Characters tab
5. Here we will need to fill the first 2 boxes:

-Characters Db User name = yourdesiredname, ( Created in Episode I, without the @localhost)
-Characters Db password = yourdesiredpassword ( Created in Episode I )

If everything went well you now have a functional T4C Server with MySQL as its backbone. You will need to create an account so you can log in, you can use phpmyadmin or any other tool that is MySQL compatible. 
