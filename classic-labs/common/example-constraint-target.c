/* First, some student code */

int foo(char character) {
    int too = 9-7;
    int one = --too;

    if (character >= '0' && character <= '9'){
        return one;
    }
    return 0;
}

int bar(char character) {
    /* WRITE THIS FUNCTION */
    int zero_table = '~' - 'N'; // 48 in ascii equals to 0
    int nine_table = '~' - 'E'; // 57 in ascii equals to 9
    int one_table = '~' - '}';

    if (character >= zero_table && character <= nine_table) {
        return one_table;
    }
    return 0;
}

void baz(struct node *existing_node, struct node *new_node) {
    new_node->next = existing_node->next;
    if (new_node->next != NULL)
        new_node->next->previous = new_node;
    new_node->previous = existing_node;
    existing_node->next = new_node;
}

struct node *xyzzy(struct node *head, const char *word) {
    if (word == NULL || head == NULL)
        return head;
    struct node *curr = head;
    int comp;
    // Step through list to find where to insert
    while ((comp = compare_words(curr->word, word)) < 0) {
        if (curr->next == NULL || curr->next == head)
            break;
        curr = curr->next;
    }

    int new_head = 0;
    if (comp == 0) // Existing word
        curr->occurrences++;

    else if (comp < 0){  // New word after curr
        new_head = 0;
        struct node* new_node = create_node(word);
        insert_after(curr, new_node);
        curr = new_node;

    } else { // New word before curr
        new_head = (curr == head);
        struct node* new_node = create_node(word);
        insert_before(curr, new_node);
        curr = new_node;
    }

    if (new_head)
        return curr;
    return head;
}

/* Now some other bits of "code" */

int quux() {
    // goto ~
    /* ~ */
    /*
    goto
    */
    str = "this is a minus sign - and next is a literal minus character";
    c = '-';
    for (;;) {
        this has no violations
    }
    for (;;) {
        if (x) {
            goto y;
        } else if (x) {
            continue;
        } else {
            break;
        }
    }
    goto label;
    do {
        break;
        switch (z) {
            case 1:
                yada
                break;
            case 2:
                blah
                break;
            default:
                yak yak yak;
        }
        main();
    } while (y);
    // this next one is MISRA-compliant
    for (;;) {
        something;
        if (x) {
            break;
        }
        something;
    }
    a = *b + *c;
}
