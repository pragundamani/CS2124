Begin and end methods return pointers to the start/end and end returns item after

By setting a copy constructor to default you use the system provider constructor

Unary operators are implemented as methods

Square bracket operator

# Components of an iterator:
- Constructor
    - No need to write a copy constructor system provided one works fine
        - implement that with `Prototype(const Prototype&) = default`
- De-reference operator
- Pre/Post increment operator
- Inequality operator
- Begin/End methods
- If begin and end are not const then it will not work 

Use templating to make a generic option
