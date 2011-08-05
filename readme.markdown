fDebug Client
=============

Usage
-----

fdebug [switches]
    
    -p, --port           bind to specified port (default: 5005)
    -d, --details        show detailed fDebug output
    -s, --strict         enable strict mode
                         fdebug will ask for accepting new incoming connections
    -V, --variables      show variables
    -S, --control        show control output
    
Message Filters:
If no message filters are specified, all messages will be displayed
    
    -m, --message        show messages
    -w, --warning        show warnings
    -e, --error          show errors
    -f, --fatal          show fatal errors
    
Extended Message Filtering:

    --match              apply filter using the fnmatch() function
    
Miscellaneous:
    
    -h, --help           display this help
    -v, --version        show version information
    -D, --debug          debug mode


Usage Examples
-----

Listen on the default port 5005 and show warning, error and fatal messages only.

    $ fdebug --warning --error --fatal


Show all messages containing the keyword ’finished’ (this would include warnings, errors and fatals too)
Please note that the pattern is matched case-sensitively

    $ fdebug --match "*finished*"


Display warning messages with detailed information

    $ fdebug -d -w


Output Example
-----

    $ fdebug
    Listen on port 5005
    Waiting for incomming connections...
    
    ---------------------------------------------------------------------------------------
    Connection from fcmstest.ahabel.dev (127.0.0.1) (/de/site/foo.xml)
    [WARNING]  Changing locale to 'de_DE' failed - using 'de_DE.UTF8' as fallback.
    [MESSAGE]  Processing language: de
    [MESSAGE]  no protocol specified - using 'conf://acl/control.xml'
    [MESSAGE]  SiteSystem: acl file 'conf://acl/control.xml' successfully loaded
    [MESSAGE]  init complete
    [FATAL]  File 'foo.xml' not found
    [WARNING]  Source is empty - cannot send
    
    Waiting for incomming connections...


