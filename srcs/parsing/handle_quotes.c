#include "../../include/minishell.h"

static bool check_quotes(bool *double_quote, bool *single_quote, int *pos, char c)
 {
    if (c == '"' && !*single_quote)
        *double_quote = !*double_quote;
    else if (c == '\'' && !*double_quote)
        *single_quote = !*single_quote;
    (*pos)++;
    return (false);
}

int handle_quotes(t_global *data, char *command) 
{
    bool single_quote;
    bool double_quote;
    int pos;

    pos = 0;
    double_quote = false;
    single_quote = false;

    while (command && command[pos]) 
        check_quotes(&double_quote, &single_quote, &pos, command[pos]);

    if (double_quote || single_quote) 
    {
        printf("Quotes are not closed\n");
        data->exit_value = 2;
        return (1);
    }

    data->exit_value = 0;
    return (0);
}

// int main() {
//     t_global data;

//     char *test1 = "LA CEST UN 'TEST' mdr";
//     char *test2 = "BHe LaAuSSI C un \"test\" lol";
//     char *test3 = "cacaca 'caca caca";
//     char *test4 = "ohlala \"bouh Ouuuuh";
//     char *test5 = "paul \"beeeh 'biquette\""; 

//     printf("Test 1: %s\n", test1);
//     handle_quotes(&data, test1);
//     printf("Exit value: %d\n\n", data.exit_value);

//     printf("Test 2: %s\n", test2);
//     handle_quotes(&data, test2);
//     printf("Exit value: %d\n\n", data.exit_value);

//     printf("Test 3: %s\n", test3);
//     handle_quotes(&data, test3);
//     printf("Exit value: %d\n\n", data.exit_value);

//     printf("Test 4: %s\n", test4);
//     handle_quotes(&data, test4);
//     printf("Exit value: %d\n\n", data.exit_value);

//     printf("Test 5: %s\n", test5);
//     handle_quotes(&data, test5);
//     printf("Exit value: %d\n", data.exit_value);
// }
