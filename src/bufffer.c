#include "headers/bufffer.h"
#include "helpers/helper_fn.h"

// Print the prompt
void print_prompt() {
    printf("db >");
}

// Read the input from the terminal
void read_input(InputBuffer *input_buffer) {
    ssize_t read_input = getline(&input_buffer->buffer, &input_buffer->buffer_length, stdin);

    if(read_input <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = read_input;
}
// To close the input_buffer
void close_input_buffer(InputBuffer *input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

// To check for meta commands
MetaCommandResult do_meta_command(InputBuffer *input_buffer) {
    if(strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    }

    printf("Unrecognized command %s\n", input_buffer->buffer);
    return META_COMMAND_UNRECOGNIZED_COMMAND;
}


// To prepare the statement types acts as parsers
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement* statement) {
    if(strncmp(input_buffer->buffer, "insert" , 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if(strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_COMMAND;

}


void execute_statement(const Statement* statement) {
    switch(statement->type) {
        case STATEMENT_SELECT:
            printf("This will do statement select\n");
        break;
        case STATEMENT_INSERT:
            printf("This will do statement insert\n");
        break;
    }
}



int main(int __argc, char *__argv[]) {
    // Initialize
    InputBuffer *input_buffer = input_buffer_new();

    while (true) {
        print_prompt();
        read_input(input_buffer);

        if(input_buffer->buffer[0] == '.') {
            switch(do_meta_command(input_buffer)) {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("Unrecognized command at meta %s\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNIZED_COMMAND:
                printf("Unrecognized command at preparation %s\n", input_buffer->buffer);
                continue;
        }
        execute_statement(&statement);
        printf("Executed command %s\n", input_buffer->buffer);
    }

    return 0;
}
