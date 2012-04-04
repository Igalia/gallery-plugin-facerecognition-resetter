Gallery Facerecognition Resetter Plugin
=======================================

What is it?
-----------

*Gallery Facerecognition Resetter Plugin* is not a real filter for the
Gallery application of the N9 (and N950) MeeGo devices. Instead, it is
just a why of forcing the deletion of the facerecognition database
through its usage from Gallery.

Accessing its functionality:
----------------------------
 * From the application grid, open Gallery.
 * Pick any picture.
 * Tap on the object menu and select *Edit*.
 * Tap on *Facerecognition resetter*.
 * Click the *Reset* button.
 * After deleting the facerecognition database, close Gallery immediately.

Known Issues:
-------------
 * You will need to reboot to make the icon for the plugin appear properly.

In depth:
---------

Gallery has a facerecognition functionality since PR1.2. This features
uses a SQLite database in which stores the learning from running the
algorithm on Gallery's pictures. Eventually, we would like to remove
this database. One of the reasons for doing so is that sometimes this
database gets corrupted and the feature stops working.

Unfortunately, this database is protected through the usage of some
AEGIS credentials so it is not possible to remove the database
manually from a terminal or another application.

As Gallery uses a plugin mechanism, it is possible to write a new
filter that, instead of acting on an image, it could be used to run
some actions with the same credentials than the ones owned by Gallery.

Therefore, this plugin is just a hack to be able to delete this
database abusing the plugin mechanism of Gallery.