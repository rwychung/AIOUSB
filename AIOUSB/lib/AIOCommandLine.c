#include "AIOCommandLine.h"

extern int opterr;
extern int optind;

#ifdef __cplusplus
namespace AIOUSB {
#endif

/**
 * @brief The default settings for running various samples. THis makes it 
 * easier to just get a sample up and running and then tweak certain parameters
 * for ones own needs. For instance, if the user wanted to perform an simple ADC_GetScan,
 * s/he could just use the settings provided in the AIO_DEFAULT_CMDLINE_OPTIONS variable
 * to get
 * - 16 channels per scan
 * - Each channel sampling at AD_GAIN_CODE_0_5V ( 0 to 5 volts )
 * - 0 Oversamples.
 * - 1000 ms timeout.
 */
AIOCommandLineOptions AIO_DEFAULT_CMDLINE_OPTIONS = {
                           0,                             /* int pass_through; */
                           -1,                            /* int64_t num_scans; */
                           10000,                         /* int64_t default_num_scans; */
                           -1,                            /* unsigned num_channels; */      
                           16,                            /* unsigned default_num_channels; */      
                           -1,                            /* unsigned num_oversamples; */   
                           0,                             /* unsigned default_num_oversamples; */   
                           AD_GAIN_CODE_0_5V ,            /* int gain_code; */              
                           -1,                            /* int clock_rate; */             
                           10000,                         /* int default_clock_rate;  */
                           (char*)"output.txt",                  /* char *outfile; */              
                           0,                             /* int reset; */                  
                           AIODEFAULT_LOG_LEVEL,          /* int debug_level; */            
                           0,                             /* int number_ranges; */          
                           0,                             /* int verbose; */                
                           -1,                            /* int start_channel; */          
                           0,                             /* int default_start_channel; */          
                           -1,                            /* int end_channel; */            
                           15,                            /* int default_end_channel; */            
                           -1,                            /* int index; */                  
                           -1,                            /* int block_size; */             
                           0,                             /* int with_timing; */            
                           0,                             /* int slow_acquire; */           
                           2048,                          /* int buffer_size; */            
                           100,                           /* int rate_limit; */             
                           0,                             /* int physical; */               
                           0,                             /* int counts; */                 
                           0,                             /* int calibration; */            
                           2,                             /* int repeat */
                           NULL,
                           (char *)"{\"DeviceIndex\":0,\"base_size\":2048,\"block_size\":65536,\"debug\":\"false\",\"hz\":10000,\"num_channels\":16,\"num_oversamples\":0,\"num_scans\":1024,\"testing\":\"false\",\"timeout\":1000,\"type\":2,\"unit_size\":2}",
                           (char*)"{\"channels\":[{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"}],\"calibration\":\"Normal\",\"trigger\":{\"reference\":\"sw\",\"edge\":\"rising-edge\",\"refchannel\":\"single-channel\"},\"start_channel\":\"0\",\"end_channel\":\"15\",\"oversample\":\"0\",\"timeout\":\"1000\",\"clock_rate\":\"1000\"}",
                           NULL
};


AIOCommandLineOptions AIO_DEFAULT_SCRIPTING_OPTIONS = {
                           1,                             /* int pass_through; */
                           -1,                            /* int64_t num_scans; */
                           10000,                         /* int64_t default_num_scans; */
                           -1,                            /* unsigned num_channels; */      
                           16,                            /* unsigned default_num_channels; */      
                           -1,                            /* unsigned num_oversamples; */   
                           0,                             /* unsigned default_num_oversamples; */   
                           AD_GAIN_CODE_0_5V ,            /* int gain_code; */              
                           -1,                            /* int clock_rate; */             
                           10000,                         /* int default_clock_rate;  */
                           (char*)"output.txt",                  /* char *outfile; */              
                           0,                             /* int reset; */                  
                           AIODEFAULT_LOG_LEVEL,          /* int debug_level; */            
                           0,                             /* int number_ranges; */          
                           0,                             /* int verbose; */                
                           -1,                            /* int start_channel; */          
                           0,                             /* int default_start_channel; */          
                           -1,                            /* int end_channel; */            
                           15,                            /* int default_end_channel; */            
                           -1,                            /* int index; */                  
                           -1,                            /* int block_size; */             
                           0,                             /* int with_timing; */            
                           0,                             /* int slow_acquire; */           
                           2048,                          /* int buffer_size; */            
                           100,                           /* int rate_limit; */             
                           0,                             /* int physical; */               
                           0,                             /* int counts; */                 
                           0,                             /* int calibration; */            
                           2,                             /* int repeat */
                           NULL,
                           (char *)"{\"DeviceIndex\":0,\"base_size\":2048,\"block_size\":65536,\"debug\":\"false\",\"hz\":10000,\"num_channels\":16,\"num_oversamples\":0,\"num_scans\":1024,\"testing\":\"false\",\"timeout\":1000,\"type\":2,\"unit_size\":2}",
                           (char*)"{\"channels\":[{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"},{\"gain\":\"0-10V\"}],\"calibration\":\"Normal\",\"trigger\":{\"reference\":\"sw\",\"edge\":\"rising-edge\",\"refchannel\":\"single-channel\"},\"start_channel\":\"0\",\"end_channel\":\"15\",\"oversample\":\"0\",\"timeout\":\"1000\",\"clock_rate\":\"1000\"}",
                           NULL
};

/*----------------------------------------------------------------------------*/
/**
 * @brief 
 * 
 * @param options 
 * @param argc Pointer to number of arguments in argv. 
 * @param argv An array of strings
 * 
 * @return 
 */
AIORET_TYPE AIOProcessCommandLine( AIOCommandLineOptions *options, int *argc, char *argv[] )
{
    int c;
    int error = 0;
    int option_index = 0;
    int query = 0;
    int dump_adcconfig = 0;
    int indprev,indafter = -1;
    int keepcount = 1, keepsize = 1,*keepindices = 0;
    keepindices = (int*)malloc(sizeof(int *)*keepsize);
    if ( !keepindices ) 
        return -AIOUSB_ERROR_INVALID_MEMORY;
    keepindices[0] = 0;
    char **oargv = 0;
    oargv = (char **)malloc(sizeof(char *)* *argc );

    memcpy( oargv, argv, sizeof(char *)* *argc ); /* Save the strings bc getopt_long 
                                                   * is known to switch order after
                                                   * processing */

    AIODisplayType display_type = BASIC;
    opterr = 0;
    char *arguments = (char *)"B:C:D:JL:N:R:S:TVYb:O:c:g:hi:m:n:o:q";

    static struct option long_options[] = {
        {"debug"            , required_argument, 0,  'D'   },
        {"dump"             , no_argument      , 0,   DUMP },
        {"dumpadcconfig"    , no_argument      , 0,   DUMP },
        {"buffer_size"      , required_argument, 0,  'S'   },
        {"num_scans"        , required_argument, 0,  'N'   },
        {"num_channels"     , required_argument, 0,  'n'   },
        {"num_oversamples"  , required_argument, 0,  'O'   },
        {"gaincode"         , required_argument, 0,  'g'   },
        {"clockrate"        , required_argument, 0,  'c'   },
        {"calibration"      , required_argument, 0 , 'C'   },
        {"help"             , no_argument      , 0,  'h'   },
        {"index"            , required_argument, 0,  'i'   },
        {"range"            , required_argument, 0,  'R'   },
        {"repeat"           , required_argument, 0,  REPEAT},
        {"reset"            , no_argument,       0,  'r'   },
        {"outfile"          , required_argument, 0,  'f'   },
        {"verbose"          , no_argument,       0,  'V'   },
        {"block_size"       , required_argument, 0,  'B'   },
        {"timing"           , no_argument      , 0,  'T'   },
        {"query"            , no_argument      , 0,  'q'   },
        {"ratelimit"        , required_argument, 0,  'L'   },
        {"physical"         , no_argument      , 0,  'p'   },
        {"counts"           , no_argument      , 0,   CNTS },         
        {"yaml"             , no_argument      , 0,  'Y'   },
        {"json"             , no_argument      , 0,  'J'   },
        {"jsonconfig"       , required_argument, 0,  JCONF },
        {0                  , 0,                 0,   0    }
    };
    while (1) { 
        AIOChannelRangeTmp *tmp;
        indprev = optind;
        c = getopt_long(*argc, argv, arguments, long_options, &option_index);
        if( c == -1 )
            break;
        switch (c) {
        case 'R':
            if( !( tmp = AIOGetChannelRange(optarg)) ) {
                fprintf(stdout,"Incorrect channel range spec, should be '--range START-END=GAIN_CODE', not %s\n", optarg );
                return -AIOUSB_ERROR_AIOCOMMANDLINE_INVALID_CHANNEL_RANGE;
            }

            options->ranges = (AIOChannelRangeTmp **)realloc( options->ranges , (++options->number_ranges)*sizeof(AIOChannelRangeTmp *)  );

            options->ranges[options->number_ranges-1] = tmp;
            break;
        case 'S':
            
            options->buffer_size = atoi( optarg );
            break;
        case 'T':
            options->with_timing = 1;
            break;
        case 'B':
            
            options->block_size = atoi( optarg );
            break;
        case 'C':
            
            options->calibration = atoi( optarg );
            if ( !VALID_ENUM( ADCalMode, options->calibration ) ) {
                fprintf(stderr,"Error: calibration %d is not valid\n", options->calibration );
                fprintf(stderr,"Acceptable values are %d,%d,%d and %d\n",
                        AD_CAL_MODE_NORMAL,
                        AD_CAL_MODE_GROUND,
                        AD_CAL_MODE_REFERENCE,
                        AD_CAL_MODE_BIP_GROUND
                        );
                fprintf(stderr, "Using default AD_CAL_MODE_NORMAL\n");
                options->calibration = AD_CAL_MODE_NORMAL;
            }
            break;
        case 'Y':
            display_type = YAML;
            break;
        case 'J':
            display_type = JSON;
            break;
        case 'p':
                options->physical = 1;
                break;
        case 'L':
            
            options->rate_limit = atoi(optarg);
            break;
        case 'q':
            query = 1;
            break;
        case 'D':
            options->debug_level = (AIO_DEBUG_LEVEL)atoi(optarg);
            AIOUSB_DEBUG_LEVEL  = (AIO_DEBUG_LEVEL)options->debug_level;
            break;
        case DUMP:
            dump_adcconfig = 1;
            break;
        case CNTS:
            options->counts = 1;
            break;
        case JCONF:
            options->aiobuf_json = strdup( optarg );
            break;
        case REPEAT:
            options->repeat = atoi(optarg);
            break;
        case 'f':
            options->outfile = strdup(optarg);
            break;
        case 'h':
            AIOPrintUsage(*argc, argv, long_options );
            return -AIOUSB_ERROR_AIOCOMMANDLINE_HELP;
            break;
        case 'i':
            options->index = atoi(optarg);
            break;
        case 'V':
            options->verbose = 1;
            break;
        case 'n':
            options->num_channels = atoi(optarg);
            break;
        case 'O':
            options->num_oversamples = atoi(optarg);
            options->num_oversamples = ( options->num_oversamples > 255 ? 255 : options->num_oversamples );
            break;
        case 'g':
            options->gain_code = atoi(optarg);
            break;
        case 'r':
            options->reset = 1;
            break;
        case 'c':
            options->clock_rate = atoi(optarg);
            break;
        case 'N':
        case 'b':
            options->num_scans = (int64_t)atoll(optarg);
            if( options->num_scans <= 0 ) {
                fprintf(stderr,"Warning: Buffer Size outside acceptable range (1,1e8), setting to 10000\n");
                options->num_scans = 10000;
            }
            break;
        default:
            if ( !options->pass_through ) {
                 fprintf(stderr, "Incorrect argument '%s'\n", optarg );
                 error = 1;
            } else {
                keepsize += (optind - indprev);
                keepindices = (int*)realloc(keepindices,sizeof(int *)*keepsize);
                for( int i = indprev; i < optind; i ++ , keepcount ++) { 
                    keepindices[keepcount] = i;
                }
            }
        }
        if ( indafter != -1 && optind - indprev >= 3 ) {
            int stop = ( long_options[option_index].has_arg ? optind - 2 : optind - 1 );
            keepsize += ( stop - indprev );
            keepindices = (int*)realloc(keepindices,sizeof(int *)*keepsize);
            for ( int i = indprev; i < stop ;i ++ , keepcount ++) { 
                keepindices[keepcount] = i;
            }
        }

        if( error ) {
            AIOPrintUsage(*argc, argv, long_options);
            return -AIOUSB_ERROR_INVALID_LIBUSB_DEVICE_HANDLE;
        }
        if( options->num_channels == 0 ) {
            fprintf(stderr,"Error: You must specify num_channels > 0: %d\n", options->num_channels );
            AIOPrintUsage(*argc, argv, long_options);
            return -AIOUSB_ERROR_AIOCOMMANDLINE_INVALID_NUM_CHANNELS;
        }
        indafter = indprev;
    }

    if ( query ) {
        AIOUSB_Init();
        AIOUSB_ShowDevices( display_type );
        return AIOUSB_SUCCESS;
    }

    if ( dump_adcconfig ) { 
        if ( options->index == -1 ) { 
            fprintf(stderr,"Error: Can't dump adcconfiguration without specifying index ( -i INDEX_NUM ) of the device\nexiting...\n");
            return -AIOUSB_ERROR_AIOCOMMANDLINE_INVALID_INDEX_NUM;
        } else {
            AIOUSB_Init();
            ADCConfigBlock config;
            ADCConfigBlockInitializeDefault( &config );
            ADC_GetConfig( options->index, config.registers, &config.size );
            printf("%s\n",ADCConfigBlockToJSON(&config));
            return AIOUSB_SUCCESS;
        }
    } 

    if ( options->number_ranges == 0 ) { 
        if ( options->start_channel >= 0 && options->end_channel >=0  && options->num_channels ) {
            fprintf(stdout,"Error: you can only specify -start_channel & -end_channel OR  --start_channel & --numberchannels\n");
            AIOPrintUsage(*argc, argv, long_options );
            return -AIOUSB_ERROR_AIOCOMMANDLINE_INVALID_START_END_CHANNEL;

        } else if ( options->start_channel >= 0 && options->num_channels >= 0 ) {
            options->end_channel = options->start_channel + options->num_channels - 1;
        } else if ( options->num_channels > 0 ) {
            options->start_channel = 0;
            options->end_channel = options->num_channels - 1;
        } else if ( options->num_channels < 0 && options->start_channel < 0 && options->end_channel < 0 ) {
            
        } else {
            options->num_channels = options->end_channel - options->start_channel  + 1;
        }
    } else {
        int min = -1, max = -1;
        for( int i = 0; i < options->number_ranges ; i ++ ) {
            if ( min == -1 )
                min = options->ranges[i]->start_channel;
            if ( max == -1 ) 
                max = options->ranges[i]->end_channel;

            min = ( options->ranges[i]->start_channel < min ?  options->ranges[i]->start_channel : min );
            max = ( options->ranges[i]->end_channel > max ?  options->ranges[i]->end_channel : max );
        }
        options->start_channel = min;
        options->end_channel = max;
        options->num_channels = (max - min + 1 );
    }
    if ( options->pass_through && keepcount > 1 ) {
        for ( int i = 1; i < keepcount ; i ++ ) {
            argv[i] = oargv[keepindices[i]];
        }
        *argc = keepcount;
        optind = keepcount + 1;


    }
    if ( keepindices ) free(keepindices);
    free(oargv);

    return AIOUSB_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/**
 * @brief A simplified command line parsing library for 
 * 
 * @param options AIOCommandLineOptions object that holds overridden cmd 
 *        line options
 * @param argc Number of command line arguments
 * @param argv Array of strings to the command line arguments
 * 
 * @return 
 */
AIORET_TYPE AIOProcessCmdline( AIOCommandLineOptions *options, int argc, char *argv[] )
{
    return AIOProcessCommandLine( options, &argc, argv );
}

/*----------------------------------------------------------------------------*/
/**
 * @brief Shows the user the various options that this library is capable
 *        of parsing on the command line.
 * @param argc Number of command line arguments
 * @param argv Array of strings to the command line arguments
 * @param options 
 */
void AIOPrintUsage(int argc, char **argv,  struct option *options)
{
    fprintf(stderr,"%s - Options\n", argv[0] );
    for ( int i =0 ; options[i].name != NULL ; i ++ ) {
        if ( options[i].val < 255 ) { 
            fprintf(stderr,"\t-%c | --%s ", (char)options[i].val, options[i].name);
        } else {
            fprintf(stderr,"\t     --%s ", options[i].name);
        }
        if( options[i].has_arg == optional_argument ) {
            fprintf(stderr, " [ ARG ]\n");
        } else if( options[i].has_arg == required_argument ) {
            fprintf(stderr, " ARG\n");
        } else {
            fprintf(stderr,"\n");
        }
    }
}

/*----------------------------------------------------------------------------*/
/**
 * @brief Creates a new command line option object for performing comparisons 
 *        with the default settings for AIOUSB devices
 * @return AIOCommandLineOptions * a new object containing the default settings
 */
AIOCommandLineOptions *NewDefaultAIOCommandLineOptions()
{
    AIOCommandLineOptions *ndef = (AIOCommandLineOptions *)malloc(sizeof(AIOCommandLineOptions));
    if ( !ndef )
        return ndef;
    memcpy( ndef, &AIO_DEFAULT_CMDLINE_OPTIONS, sizeof( AIOCommandLineOptions ));
    return ndef;
}

/*----------------------------------------------------------------------------*/
AIOCommandLineOptions *NewAIOCommandLineOptionsFromDefaultOptions(AIOCommandLineOptions *orig )
{
    AIO_ASSERT_RET( NULL, orig != NULL );
    AIOCommandLineOptions *ndef = (AIOCommandLineOptions *)malloc(sizeof(AIOCommandLineOptions));
    if ( !ndef )
        return ndef;
    memcpy( ndef, orig, sizeof( AIOCommandLineOptions ));
    return ndef;
}


/*----------------------------------------------------------------------------*/
/**
 * @brief A Descructor for the allocated AIOCommandLineOptions
 * 
 * @param options 
 * 
 * @return 
 */
AIORET_TYPE DeleteAIOCommandLineOptions( AIOCommandLineOptions *options )
{
    AIO_ASSERT( options );
    for ( int i = 0; i < options->number_ranges ; i ++ ) { 
        free(options->ranges[i]);
    }
    free(options->ranges);
    free( options );
    return AIOUSB_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/**
 * @brief Returns the index that the user has specified on the command line
 * for running the test on.
 * @param options 
 * 
 * @return >= 0 is a valid index, < 0 indicated error
 */
AIORET_TYPE AIOCommandLineOptionsGetDeviceIndex( AIOCommandLineOptions *options )
{
    AIO_ASSERT( options );
    return options->index;
}

/*----------------------------------------------------------------------------*/
/**
 * @brief Lists any devices that were matched and then lists which index was
 *        specified.
 * @param options AIOCommandLineOptions object
 * @param indices Array of devices found
 * @param num_devices number of devices in the array
 * @return >= AIOUSB_SUCCESS if devices have been found, < 0 if no devices found
 */
AIORET_TYPE AIOCommandLineListDevices( AIOCommandLineOptions *options , int *indices, int num_devices )
{
    AIORET_TYPE retval = AIOUSB_SUCCESS;
    AIOUSB_ListDevices();
    if ( num_devices <= 0 ) {
        fprintf(stderr,"No devices were found\n");
        retval = -AIOUSB_ERROR_DEVICE_NOT_FOUND;
    } else {
        if ( options->index < 0 ) 
            options->index = indices[0];
        fprintf(stderr,"Matching devices found at indices: ");
        options->index = ( options->index < 0 ? indices[0] : options->index );
        int i;
        for (i = 0; i < num_devices - 1; i ++ ) { 
            fprintf(stderr, "%d",indices[i] );
            if ( num_devices > 2 )
                fprintf(stderr,", "); 
        }
        if ( num_devices > 1 ) 
            fprintf(stderr," and ");

        fprintf(stderr, "%d , Using index=%d \n",indices[i], options->index);
    }
    return retval;

}

/*----------------------------------------------------------------------------*/
/**
 * @brief Allows the AIOCommandLineOptions options to override the settings in 
 *        the ADCConfigBlock
 * @param config ADCConfigBlock object that is written to the AIOUSB device
 * @param options AIOCommandLineOptions object that represents the set of user
 *        parameters specified on the command line
 * @return >= AIOUSB_SUCCESS is successful, < 0 if there was an error
 */
AIORET_TYPE AIOCommandLineOverrideADCConfigBlock(  ADCConfigBlock *config, AIOCommandLineOptions *options)
{
    AIO_ASSERT( options );
    AIO_ASSERT( config );
    AIORET_TYPE retval = AIOUSB_SUCCESS,retval2 = AIOUSB_SUCCESS;
    
    AIOUSBDevice *dev = AIODeviceTableGetDeviceAtIndex( options->index , (AIORESULT*)&retval );
    AIO_ERROR_VALID_DATA( retval, retval == AIOUSB_SUCCESS );

    ADCConfigBlock *hwconfig = AIOUSBDeviceGetADCConfigBlock( dev );
    memcpy(&config->mux_settings, &hwconfig->mux_settings, sizeof( hwconfig->mux_settings ) );

    if ( options->num_oversamples < 0 ) { 
        retval = ADCConfigBlockSetOversample( config, options->default_num_oversamples );
        AIO_ERROR_VALID_DATA( retval, retval == AIOUSB_SUCCESS );
    } else {
        retval = ADCConfigBlockSetOversample( config, options->num_oversamples );
        AIO_ERROR_VALID_DATA( retval, retval == AIOUSB_SUCCESS );
    }
    
    if( !options->number_ranges ) {
        retval = ADCConfigBlockSetAllGainCodeAndDiffMode( config , options->gain_code , AIOUSB_FALSE );
        AIO_ERROR_VALID_DATA( retval, retval == AIOUSB_SUCCESS );
    } else {
        for ( int i = 0; i < options->number_ranges ; i ++ ) {
            retval = ADCConfigBlockSetChannelRange( config, 
                                                    options->ranges[i]->start_channel,
                                                    options->ranges[i]->end_channel,
                                                    options->ranges[i]->gaincode 
                                                    );                                          
            if ( retval != AIOUSB_SUCCESS ) {
                fprintf(stderr,"Error setting ChannelRange: %d\n", (int)retval );
                return retval;
            }
        }
        /* also set the range for the buffer */
        retval = ADCConfigBlockSetStartChannel( config, options->start_channel );
        retval2 = ADCConfigBlockSetEndChannel( config, options->end_channel );
        if ( retval != AIOUSB_SUCCESS || retval2 != AIOUSB_SUCCESS ) {
            fprintf(stderr,"Error trying to set StartCh=%d and EndCh=%d...%d\n", 
                    options->start_channel, 
                    options->end_channel,
                    (int)retval
                    );
            return retval;
        }
    }
  
    return retval;
}

/*----------------------------------------------------------------------------*/
AIOChannelRangeTmp *AIOGetChannelRange(char *optarg )
{
    int i = 0;
  
    typedef enum { 
        BEGIN = 0,
        SCHANNEL,
        ECHANNEL,
        GAIN,
    } MODE;
    int pos;
    char buf[BUFSIZ];
    AIOChannelRangeTmp *tmp = (AIOChannelRangeTmp *)malloc( sizeof(AIOChannelRangeTmp) );
    if ( !tmp ) {
        fprintf(stdout,"Unable to create a new channel range\n");
        return NULL;
    }
    MODE mode = BEGIN;
    for ( i = 0; i < (int)strlen(optarg); i ++ ) {
        if ( mode == BEGIN && isdigit(optarg[i] ) ) {
            pos = i;
            mode = SCHANNEL;
        } else if ( mode == SCHANNEL && isdigit(optarg[i])  ) {
      
        } else if ( mode == SCHANNEL && optarg[i] == '-' ) {
            mode = ECHANNEL;
            strncpy(&buf[0], &optarg[pos], i - pos );
            buf[i-pos] = 0;
            tmp->start_channel = atoi(buf);
            i ++ ;
            pos = i;
        } else if ( mode == SCHANNEL ) {
            fprintf(stdout,"Unknown flag while parsing Start_channel: '%c'\n", optarg[i] );
            free(tmp);
            return NULL;
        } else if ( mode == ECHANNEL && isdigit(optarg[i] ) ) {
      
        } else if ( mode == ECHANNEL && optarg[i] == '=' ) {
            mode = GAIN;
            strncpy(&buf[0], &optarg[pos], i - pos );
            buf[i-pos] = 0;
            tmp->end_channel = atoi(buf);
            i ++;
            strncpy(&buf[0], &optarg[i],strlen(optarg));
            tmp->gaincode = atoi( buf );
            break;
        } else {
            fprintf(stdout,"Unknown flag while parsing End_channel: '%c'\n", optarg[i] );
            free(tmp);
            return NULL;
        }
    }
    return tmp;
}



#ifdef __cplusplus
}
#endif

/*****************************************************************************
 * Self-test 
 * @note This section is for stress testing the DIO code without using the USB 
 * features
 *
 ****************************************************************************/ 

#ifdef SELF_TEST

#include "AIOUSBDevice.h"
#include "gtest/gtest.h"

#include <iostream>
using namespace AIOUSB;

TEST( AIOCmdLine, CorrectDefaults )
{
    AIOCommandLineOptions *nopts = NewDefaultAIOCommandLineOptions();
    ASSERT_TRUE( nopts );

    ASSERT_EQ( 0, nopts->default_num_oversamples );

    ASSERT_EQ( AD_GAIN_CODE_0_5V, nopts->gain_code );

    DeleteAIOCommandLineOptions( nopts );

}

TEST( AIOCmdLine, CorrectlyDies )
{
    AIOCommandLineOptions *nopts = NULL;
    ASSERT_DEATH( {AIOCommandLineOptionsGetDeviceIndex(nopts); },"Assertion `options' failed"); 
}

TEST( AIOCmdLine, CmdlineParsing )
{
    AIOCommandLineOptions *nopts = NewDefaultAIOCommandLineOptions();
    AIORET_TYPE retval;
    ASSERT_TRUE( nopts );
    char *argv[] = {(char *)"foo",(char *)"-N",(char *)"1000"};
    int argc = 3;

    ASSERT_EQ( 0, nopts->default_num_oversamples );

    ASSERT_EQ( AD_GAIN_CODE_0_5V, nopts->gain_code );

    retval = AIOProcessCmdline( nopts, argc, argv );

    ASSERT_EQ(3, optind );

    ASSERT_GE( retval, AIOUSB_SUCCESS );

    DeleteAIOCommandLineOptions( nopts );
}

TEST(AIOCmdLine, NewOptions )
{

    AIOCommandLineOptions *nopts = NewAIOCommandLineOptionsFromDefaultOptions( &AIO_DEFAULT_CMDLINE_OPTIONS );
    ASSERT_TRUE( nopts );
    
    ASSERT_EQ( 0, memcmp(nopts, &AIO_DEFAULT_CMDLINE_OPTIONS, sizeof(AIOCommandLineOptions)));
    
    DeleteAIOCommandLineOptions( nopts );
}

TEST( AIOCmdLine, LargerParsingTest )
{
    AIOCommandLineOptions *nopts = NewAIOCommandLineOptionsFromDefaultOptions(&AIO_DEFAULT_SCRIPTING_OPTIONS);
    AIORET_TYPE retval;
    ASSERT_TRUE( nopts );
    char *tmp = (char *)"--foobar";
    char *argv[] = {(char *)"foo",(char *)"-N",(char *)"1000",(char *)"--foobar",(char *)"--args",
                    (char*)"--range",(char *)"0-4=5,5-9=2",(char *)"--clockrate",(char*)"40000",
                    (char *)"--buffer_size",(char *)"343434" };

    int argc = sizeof(argv)/sizeof(char*);
    optind = 1;

    retval = AIOProcessCommandLine( nopts, &argc, argv );
    ASSERT_GE( retval, AIOUSB_SUCCESS );

    ASSERT_EQ(3, argc ) << "should be removed leaving us with 3 args\n";

    ASSERT_EQ(4, optind );

    EXPECT_STREQ( argv[0], (char*)"foo" );

    EXPECT_STREQ( argv[1], tmp );

    EXPECT_STREQ( argv[2], (char *)"--args" );

    DeleteAIOCommandLineOptions( nopts );
}

TEST( AIOCmdLine, StrangeArguments )
{
    AIOCommandLineOptions *nopts = NewAIOCommandLineOptionsFromDefaultOptions(&AIO_DEFAULT_SCRIPTING_OPTIONS);
    AIORET_TYPE retval;
    ASSERT_TRUE( nopts );
    char *tmp = (char *)"--foobar";
    char *argv[] = {(char *)"foo",(char *)"-N",(char *)"1000",(char *)"--foobar",(char *)"3434",(char *)"3434",
                    (char*)"--range",(char *)"0-4=5,5-9=2",(char *)"--clockrate",(char*)"40000",
                    (char *)"--buffer_size",(char *)"343434" };

    int argc = sizeof(argv)/sizeof(char*);
    optind = 1;

    retval = AIOProcessCommandLine( nopts, &argc, argv );
    ASSERT_GE( retval, AIOUSB_SUCCESS );

    ASSERT_EQ(4, argc ) << "should be removed leaving us with 3 args\n";

    ASSERT_EQ(5, optind );

    EXPECT_STREQ( argv[0], (char*)"foo" );

    EXPECT_STREQ( argv[1], tmp );

    EXPECT_STREQ( argv[2], (char *)"3434" );

    DeleteAIOCommandLineOptions( nopts );
}







#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[] )
{
  
  AIORET_TYPE retval;

  testing::InitGoogleTest(&argc, argv);
  testing::TestEventListeners & listeners = testing::UnitTest::GetInstance()->listeners();

  return RUN_ALL_TESTS();  

}

#endif
