STAD
====

Description
-----------

STAD is a plugin developed for preventing SQL injection attacks. It is a practical protection mechanism that applies the concept of instruction-set randomization to SQL: the SQL standard keywords are modified by appending a random key to them, one that an attacker cannot easily guess. Queries injected by an attacker into a randomized query will be caught since they will not contain the randomization key. The plugin will then just execute a harmless query (for now it is 'SELECT 1') instead of returning any error information to a potential attacker.

The security of this approach is dependent on attackers not being able to discover the randomization key. If the key is exposed to an attacker, they will have the ability to inject SQL with the appropriate key appended to keywords.

When the plugin is loaded and a randomization key is specified, all queries issued against the database must contain the correct randomization key or they will not execute correctly. A version of the drizzle command line client comes with the plugin that automatically appends the correct randomization key to SQL keywords. When the plugin is loaded and a randomization key is specified, an administrator is encouraged to use this version of the drizzle command line client.

Configuration
-------------

Currently, there is only one variable associated with the plugin which can control the randomization key.

**key**

   Value for the randomization key. Default is empty so no randomization occurs.

What does STAD mean?
--------------------

stad is the Irish for prevent.

