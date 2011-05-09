#include "string.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include "fdebugconfig.h"
#include "global.h"

fDebugConfig* fDebugConfig::m_pInstance = NULL;

fDebugConfig* fDebugConfig::getInstance() {
   if (!m_pInstance) {  // Only allow one instance of class to be generated.
      m_pInstance = new fDebugConfig;
   }
   return m_pInstance;
}

void fDebugConfig::init(int argc, char **argv) {
	// set defaults
	debugOptions options;
	options.port      = DEFAULT_PORT;
	options.control   = false;
	options.details   = false;
	options.variables = false;
	options.strict    = false;
	options.filter    = false;
	options.debug     = false;
	
	displayFilter filter;
	filter.message   = false;
	filter.warning   = false;
	filter.error     = false;
	filter.fatal     = false;
	

	extern char *optarg;
	extern int optind;
	
	static const struct option long_options[] =
	       {
	           { "help",     no_argument,       0, 'h' },
	           { "version",  no_argument,       0, 'v' },
	           { "port",     required_argument, 0, 'p' },
	           { "details",  no_argument,       0, 'd' },
	           { "strict",   no_argument,       0, 's' },
	           { "variables",no_argument,       0, 'V' },
	           { "control",  no_argument,       0, 'S' },
	           
	           { "message",  no_argument,       0, 'm' },
	           { "error",    no_argument,       0, 'e' },
	           { "warning",  no_argument,       0, 'w' },
	           { "fatal",    no_argument,       0, 'f' },
	           { "debug",    no_argument,       0, 'D' },

	           { "match",    required_argument, 0, 'M'},
	          0
	      };
	
	while (optind < argc) {
		int index = -1;
      struct option * opt = 0;
      int result = getopt_long(argc, argv, "+hvp:dVSsmwefoDM", long_options, &index);
      if (result == -1) break; /* end of list */
      switch (result) {
      	// Usage
       	case 'h':
       		printUsage();
       		break;
       	case 'v':
       	   exit(1);
       	   break;
       	case 'p':
       		if (atoi(optarg)>0) {
       			options.port = atoi(optarg);
       		}
        	  	break;
       	case 'd':
       		options.details = true;
       		break;
       	case 's':
       	   options.strict = true;
       	   break;
       	case 'V':
        		options.variables = true;
        		break;
        	case 'S':
        		options.control = true;
        		break;
        	
         // message filter
        	case 'm':
        		filter.message = true;
        		break;
        	case 'w':
        		filter.warning = true;
        		break;
        	case 'e':
        		filter.error = true;
        		break;
        	case 'f':
        		filter.fatal = true;
        		break;

        	case 'D':
        	   options.debug = true;
        	   printf("Starting in debug mode\n");
        	   break;

        	// filter settings
        	case 'M':
            options.filter = true;
            messageFilter mf;
            mf.type    = FILTER_FNMATCH;
            mf.pattern = optarg;
            options.filterList = mf;
        	   break;

        	// fallback
        	case 0: /* all parameter that do not */
        		/* appear in the optstring */
        		opt = (struct option *)&(long_options[index]);
        		printf("'%s' was specified.", opt->name);
            if (opt->has_arg == required_argument) {
                printf("Arg: <%s>", optarg);
            }
            
            printf("\n");
            break;
        	default: /* unknown */
        		break;
       	}
   }
	
   /* print all other parameters */
   while (optind < argc) {
   	printf("other parameter: <%s>\n", argv[optind++]);
   }
	
   this->initDisplayFilter(filter);
   this->options = options;
}

void fDebugConfig::initDisplayFilter(displayFilter filter) {
	if (!filter.message && !filter.warning && !filter.error && !filter.fatal) {
		filter.message   = true;
		filter.warning   = true;
		filter.error     = true;
		filter.fatal     = true;
	}
	this->filter = filter;
}

int fDebugConfig::getPort() {
	return this->options.port;
}

void fDebugConfig::printUsage() {
	printf("Usage:\n");
	printf("  -p, --port           bind to specified port (default: 5005)\n");
	printf("  -d, --details        show detailed fDebug output\n");
	printf("  -s, --strict         enable strict mode\n");
	printf("                       fdebug will ask for accepting new incoming connections\n");
	printf("  -V, --variables      show variables\n");
	printf("  -S, --control        show control output\n");
	
	
	printf("\nMessage Filters:\n");
	printf("  If no message filters are specified, all messages will be displayed\n\n");
	printf("  -m, --message        show messages\n");
	printf("  -w, --warning        show warnings\n");
	printf("  -e, --error          show errors\n");
	printf("  -f, --fatal          show fatal errors\n\n");

	printf("Extended Message Filtering:\n");
	printf("  --match              apply filter using the fnmatch() function\n\n");
	//NEW FEATURE -- printf("  -i, --ignore-case    ignore case distinctions\n");
	//NEW FEATURE -- printf("  -I, --invert-match   show non-matching lines only\n\n");
	//NEW FEATURE -- printf("  --regex              apply a regular expression\n\n");

	printf("Miscellaneous:\n");
	printf("  -h, --help           display this help\n");
	printf("  -v, --version        show version information\n");
	printf("  -D, --debug          debug mode\n\n");
	exit(0);
}
