
## INI files
INI files contain data in basic text format

The structure of INI file is the following:
```
[section1]
key1 = value1
key2 = value2
key3 = value3


; comment

[section2]
key4 = value4
key5 = value5
key6 = value6
```
There are:

Sections with names between brackets
Pairs of keys and values
Empty lines
Comments

* The program should accept two command line parameters in the format:
```
$ ./program PATH-TO-INI-FILE.ini section.key
```
For example:
```
$ ./PharseIniFiles temp.ini section1.key1
```
* Program must print out the value of key in the given section

* For the example above, the program has to print out value under velocity key in [data] section

* Program must detect a missing section and print out dedicated message e.g. Failed to find section [data]

* Program must detect a missing key in a present section e.g. Failed to find key "velocity" in section [data]

* Program must detect invalid identifiers in INI file (section names and keys) i.e. those which contain characters other than letters and digits
