/*
 *  * Simple example demonstrating the communication between
 *   * a client and the FPGA device
 *    */

#include <mdp.h>
#include <czmq.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <bpm_client.h>

#define DFLT_BIND_FOLDER            "/tmp/bpm"

#define DFLT_BPM_NUMBER                     0
#define MAX_BPM_NUMBER                      1

#define DFLT_BOARD_NUMBER                   0
#define MAX_BOARD_NUMBER                    5

void print_help (char *program_name)
{
    printf( "Usage: %s [options]\n"
            "\t-h This help message\n"
            "\t-v Verbose output\n"
            "\t-board <AMC board = [0|1|2|3|4|5]>\n"
            "\t-bpm <BPM number = [0|1]>\n"
            "\t-b <broker_endpoint> Broker endpoint\n"
            "\t-pll_status PLL Lock status\n"
            "\t-trig_dir <dir> Trigger direction\n"
            , program_name);
}

int main (int argc, char *argv [])
{
    int verbose = 0;
    char *broker_endp = NULL;
    char *board_number_str = NULL;
    char *bpm_number_str = NULL;
    char *trig_dir_str = NULL;
    uint32_t get_pll_status = 0;
    char **str_p = NULL;

    if (argc < 3) {
        print_help (argv[0]);
        exit (1);
    }

    /* FIXME: This is rather buggy! */
    /* Simple handling of command-line options. This should be done
     *      * with getopt, for instance*/
    int i;
    for (i = 1; i < argc; i++)
    {
        if (streq(argv[i], "-v")) {
            verbose = 1;
        }
        else if (streq(argv[i], "-h"))
        {
            print_help (argv [0]);
            exit (1);
        }
        else if (streq(argv[i], "-board"))
        {
            str_p = &board_number_str;
        }
        else if (streq(argv[i], "-bpm"))
        {
            str_p = &bpm_number_str;
        }
        else if (streq (argv[i], "-b")) {
            str_p = &broker_endp;
        }
        else if (streq(argv[i], "-pll_status"))
        {
            get_pll_status = 1;
        }
        else if (streq (argv[i], "-trig_dir")) {
            str_p = &trig_dir_str;
        }
        /* Fallout for options with parameters */
        else {
            *str_p = strdup (argv[i]);
        }
    }

    /* Set default broker address */
    if (broker_endp == NULL) {
        broker_endp = strdup ("ipc://"DFLT_BIND_FOLDER);
    }

    /* Set default board number */
    uint32_t board_number;
    if (board_number_str == NULL) {
        fprintf (stderr, "[client:fmc130m_4ch]: Setting default value to BOARD number: %u\n",
                DFLT_BOARD_NUMBER);
        board_number = DFLT_BOARD_NUMBER;
    }
    else {
        board_number = strtoul (board_number_str, NULL, 10);

        if (board_number > MAX_BOARD_NUMBER) {
            fprintf (stderr, "[client:fmc130m_4ch]: BOARD number too big! Defaulting to: %u\n",
                    MAX_BOARD_NUMBER);
            board_number = MAX_BOARD_NUMBER;
        }
    }

    /* Set default bpm number */
    uint32_t bpm_number;
    if (bpm_number_str == NULL) {
        fprintf (stderr, "[client:fmc130m_4ch]: Setting default value to BPM number: %u\n",
                DFLT_BPM_NUMBER);
        bpm_number = DFLT_BPM_NUMBER;
    }
    else {
        bpm_number = strtoul (bpm_number_str, NULL, 10);

        if (bpm_number > MAX_BPM_NUMBER) {
            fprintf (stderr, "[client:fmc130m_4ch]: BPM number too big! Defaulting to: %u\n",
                    MAX_BPM_NUMBER);
            bpm_number = MAX_BPM_NUMBER;
        }
    }

    /* Generate the service names for each SMIO */
    char service[50];
    sprintf (service, "BPM%u:DEVIO:FMC130M_4CH%u", board_number, bpm_number);

    bpm_client_t *bpm_client = bpm_client_new (broker_endp, verbose, NULL);

    bpm_client_err_e err = BPM_CLIENT_SUCCESS;
    uint32_t trig_dir = 0;
    if (trig_dir_str != NULL) {
        trig_dir = strtoul (trig_dir_str, NULL, 10);

        fprintf (stdout, "[client:fmc130m_4ch]: trig_dir = %u\n", trig_dir);
        err = bpm_set_trig_dir (bpm_client, service, trig_dir);
        if (err != BPM_CLIENT_SUCCESS){
            fprintf (stderr, "[client:fmc130m_4ch]: bpm_set_trig_dir failed\n");
            goto err_bpm_exit;
        }
        fprintf (stdout, "[client:fmc130m_4ch]: bpm_set_trig_dir was successfully executed\n");
    }

    if (get_pll_status) {
        uint32_t pll_status = 0;
        bpm_client_err_e err = bpm_get_fmc_pll_status (bpm_client, service, &pll_status);
        if (err != BPM_CLIENT_SUCCESS){
            fprintf (stderr, "[client:fmc130m_4ch]: bpm_get_fmc_pll_status failed\n");
            goto err_bpm_exit;
        }
        fprintf (stdout, "[client:fmc130m_4ch]: bpm_get_fmc_pll_status: 0x%08X\n",
                pll_status);
    }

err_bpm_exit:
    bpm_client_destroy (&bpm_client);
    str_p = &trig_dir_str;
    free (*str_p);
    trig_dir_str = NULL;
    str_p = &broker_endp;
    free (*str_p);
    broker_endp = NULL;
    str_p = &board_number_str;
    free (*str_p);
    board_number_str = NULL;
    str_p = &bpm_number_str;
    free (*str_p);
    bpm_number_str = NULL;

    return 0;
}