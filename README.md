Gallery Facerecognition Resetter Plugin
=======================================

What is it?
-----------

*Gallery Facerecognition Resetter Plugin* is not a real filter for the
Gallery application of the N9 (and N950) MeeGo devices. Instead, it is
just a why of forcing the deletion or un/protection of the
facerecognition database through its usage from Gallery.

Accessing its functionality:
----------------------------
 * From the application grid, open Gallery.
 * Pick any picture.
 * Tap on the object menu and select *Edit*.
 * Tap on *Facerecognition resetter*.
 * Click the *Reset*, *Protect* and/or *Unprotect" button/s.
 * If you have deleted the facerecognition database, close Gallery immediately.

Known Issues:
-------------
 * Only *PR >= 1.2* is currently supported.
 * You will need to reboot to make the icon for the plugin appear properly.

In depth:
---------

Gallery has a facerecognition functionality since PR1.2. This features
uses a SQLite database in which stores the learning from running the
algorithm on Gallery's pictures.

This database is protected through the usage of some AEGIS credentials
so it is not possible to remove, read or write the database manually
from a terminal or another application.

Eventually, we would like to remove or un/protect this database. One
of the reasons for doing so is that sometimes this database gets
corrupted and the feature stops working.

Also, it seems that the protection makes the feature to work oddly, so
it is better to have the DB unprotected.

As Gallery uses a plugin mechanism, it is possible to write a new
filter that, instead of acting on an image, it could be used to run
some actions with the same credentials than the ones owned by Gallery.

Therefore, this plugin is just a hack to be able to delete this
database abusing the plugin mechanism of Gallery.