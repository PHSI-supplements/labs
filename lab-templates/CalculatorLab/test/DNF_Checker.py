import re

def check_dnf_return(statement: str, maximum_variables_per_minterm: int) -> bool:
    """
    Prints a message about whether `statement` complies with the assignment's
    requirements. Specifically, if it is a `return` statement, is the return expression
    in Disjunctive Normal Form, with at most `maximum_variables_per_minterm` in
    each of the product terms?

    :param statement: the return statement to be checked
    :param maximum_variables_per_minterm: the maximum number of variables allowed in a minterm
    :return: `True` if this should be considered a passing test; `False` otherwise.

    We aren't testing anything but return statements.
    >>> check_dnf_return('a = b + c;', 3)
    Not a return statement.
    True

    We're only testing return statements that have expressions.
    >>> check_dnf_return('return;', 3)
    Empty return expression.
    True

    If we can't see the whole return statement, we can't check if the expression is in DNF.
    >>> check_dnf_return('return !B0 || (B1 && B2) ||', 3)
    Not a complete return statement; cannot evaluate for DNF compliance.
    False

    The starter code does not have DNF return expressions.
    >>> check_dnf_return('return 0;', 3)
    Invalid variable, or expression is not a sum-of-products.
    False

    A single variable is DNF.
    >>> check_dnf_return('return B0;', 3)
    True

    As is a negated variable.
    >>> check_dnf_return('return !B0;', 3)
    True

    Variables other than those specified in the assignment are not allowed.
    >>> check_dnf_return('return C0;', 3)
    Invalid variable, or expression is not a sum-of-products.
    False

    You don't need to put the product terms in parentheses
    >>> check_dnf_return('return B0 && !B1 || B2;', 3)
    True

    But's it improves readability if you do so.
    >>> check_dnf_return('return (B0 && !B1) || B2;', 3)
    True

    A product term with too many variables is not allowed.
    >>> check_dnf_return('return (B0 && !B1 && !B2 && B3);', 3)
    Has a minterm with too many variables.
    False

    This semester, we aren't limiting the number of product terms.
    >>> check_dnf_return('return B0 || B1 || (B2) || !B3 || (!B1 && !B2) || (!B0 && B3) || (!B0 && B1 && B3);', 3)
    True

    Negating a non-trivial product term violates DNF.
    >>> check_dnf_return('return !(B0 && B1) || B2;', 3)
    Invalid variable, or expression is not a sum-of-products.
    False

    An OR operator inside a product term violates DNF.
    >>> check_dnf_return('return (B0 && B1 || B2) || B3;', 3)
    Invalid variable, or expression is not a sum-of-products.
    False

    You can use logical AND/OR (as above) or bitwise AND/OR.
    >>> check_dnf_return('return (B0 & !B1) | B2;', 3)
    True

    You should use logical NOT instead of bitwise complement -- but that's more about correctness than compliance.
    >>> check_dnf_return('return (B0 & ~B1) | B2;', 3)
    Invalid variable, or expression is not a sum-of-products.
    False

    Bitwise XOR violates DNF.
    >>> check_dnf_return('return (B0 & !B1) ^ B2;', 3)
    Invalid variable, or expression is not a sum-of-products.
    False
    """

    valid_variable_pattern: str = r'!?B[0-3]'   ## TODO we might want to make this a parameter

    # If the statement doesn't start with `return` then we won't evaluate it.
    if not re.match(r'^\s*return\b', statement):
        print("Not a return statement.")
        return True

    # If the statement doesn't include the semicolon, then there's some part of the expression that we can't check
    if not re.search(r';\s*$', statement):
        print("Not a complete return statement; cannot evaluate for DNF compliance.")
        return False

    expression: str = re.sub(r'^\s*return\b', '', statement)
    expression = re.sub(r';\s*$', '', expression).strip()
    if not expression:
        print('Empty return expression.')
        return True

    # Split into minterms
    minterms: list[str] = re.split(r'\|\||\|', expression)
    if not minterms:
        print('No return expression to evaluate for DNF compliance.')
        return True
    ## TODO if we later cap the number of minterms, here is the place to do it

    is_dnf_compliant: bool = True
    for minterm in minterms:
        minterm = minterm.strip()
        if minterm.startswith('(') and minterm.endswith(')'):
            minterm = minterm[1:-1].strip()
            # we don't need to explicitly check for '!(...)' because that doesn't start with '('
        variables: list[str] = re.split(r'&&|&', minterm)
        if not variables:
            print('Contains an empty minterm.')
            is_dnf_compliant = False
        elif len(variables) > maximum_variables_per_minterm:
            print('Has a minterm with too many variables.')
            is_dnf_compliant = False
        else:
            for variable in variables:
                variable = variable.strip()
                if is_dnf_compliant and not re.fullmatch(valid_variable_pattern, variable.strip()):
                    print('Invalid variable, or expression is not a sum-of-products.')
                    is_dnf_compliant = False

    return is_dnf_compliant
