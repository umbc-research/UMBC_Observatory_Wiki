# UMBC_Observatory_Wiki

These are some of the files created to add extra functionality to the wiki.

In /var/www/html/bin place the "create_blog.cpp" program and compile it as "blog"

`gcc create_blog.cpp -lstdc++ -o blog`


Now set up a system service for "blog_monitor.sh" Note you will need modify "$PATH" in the script to be where ever you blog pages reside.
service should look something like this:
```
[Unit]
Description=Monitoring the Blog namespace of the wiki server for changes

[Service]
ExecStart=/bin/blog_monitor.sh
User=root

[Install]
WantedBy=multi-user.target
```

The "blog_monitor.sh" script invokes a monitoring inotifywait thingy to check the ...../blog/ directory for created/deleted files
Upon such an event, the /bin/blog exec is run which is also stored in /bin/blog and the code is in /var/www/html/bin/create_blog.cpp (compiled with command gcc create_blog.cpp -lstdc++ -o blog)

