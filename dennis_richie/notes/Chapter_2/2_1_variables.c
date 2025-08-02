// section 2_1 to 2_4- variables and its types
// syn: [storage_class_specifier] [type_qualifier] type_specifier variable_name [= initializer];
    // Storage classes: // Auto (default for all local vars)
                        // Register (at register, lifetime of that of local var)
                        // static (Onlt within this file)
                        // extern (global i.e. All files within compilation or current file only.)

    // Types:   // char (1 byte)
                // int   (4 bytes) hold 0  to  2^32 - 1 in unsigned
                // float (4 bytes) hold extreme large due to exp bits
                // double (8 bytes)
                // long double (8 bytes of MSMV; 16 bytes for a 86X64)

    // type qualifiers: behaviour of the types
                        // const    (cannot modify variable; compiler makes it to read only mode)
                        // volatile (makes the compiler not aggressively optimize allowing unexpected read/write)
                        // restrict (latest vers of C; eliminating aliasing assumptions of compiler, so a pointer is the only way to access the object it points to within its scope.)