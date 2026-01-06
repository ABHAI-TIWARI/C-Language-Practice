


## Correct defination of main

# C Tutorial: The Many Faces of `main`

In C programming, `main` is the entry point of your application. While you may see different variations like `void main()` or `int main()`, not all of them are standard or safe to use. This guide explains the differences and why `int main(void)` or `int main(int argc, char *argv[])` are the gold standards.

***

## 1. The Standard Definition: `int main(void)`
This is the **recommended** and standard-compliant way to define `main` when your program does not need command-line arguments.[2][8]

**Syntax:**
```c
int main(void) {
    // Your code here
    return 0;
}
```

*   **`int` Return Type**: The operating system expects the program to return an integer status code when it finishes. `0` typically means "success," while non-zero values indicate errors.[1][2]
*   **`(void)` Parameter**: Explicitly stating `void` tells the compiler that this function accepts **absolutely no arguments**. In older C standards (before C23), empty parentheses `()` meant "an unspecified number of arguments," so `(void)` was safer and more precise.[8]

***

## 2. The Command-Line Definition: `int main(int argc, char *argv[])`
This is the second **standard-compliant** form, used when you need to pass input to your program from the terminal (like `./program argument1`).[2]

**Syntax:**
```c
int main(int argc, char *argv[]) {
    // Your code here
    return 0;
}
```

*   **`argc` (Argument Count)**: An integer representing the number of arguments passed (including the program name itself).
*   **`argv` (Argument Vector)**: An array of strings containing the actual arguments.

***

## 3. The "Lazy" Definition: `int main()`
You will often see this in tutorials and textbooks. In modern C (C99 and later), this is effectively treated the same as `int main(void)` in terms of behavior, but there is a subtle historical difference.[8]

**Syntax:**
```c
int main() {
    // Your code here
    return 0;
}
```

*   **What's Different?**: Technically, in older C standards, empty parentheses `()` meant the function took an *unspecified* number of arguments, whereas `(void)` meant *zero* arguments.
*   **Verdict**: Acceptable in most modern contexts, but `int main(void)` is technically more rigorous.[8]

***

## 4. The Non-Standard Definition: `void main()`
**Avoid this.** You might see `void main()` in old Turbo C++ tutorials or specific embedded systems code, but it is **not standard C**.[1][2]

**Syntax:**
```c
void main() {
    // Code
}
```

*   **The Problem**: The C standard mandates that `main` must return an `int`. Declaring it as `void` (returning nothing) can confuse the operating system or startup code that expects a status value.[1]
*   **Why it exists**: Some ancient compilers allowed it, but using it today makes your code non-portable and technically invalid.[2]

***

## Summary Table

| Definition | Standard Compliant? | Usage Scenario |
| :--- | :--- | :--- |
| **`int main(void)`** | ✅ Yes | Best for simple programs with no inputs. |
| **`int main(int argc, char *argv[])`**| ✅ Yes | Required for processing command-line arguments. |
| **`int main()`** | ⚠️ Mostly | Acceptable, but `(void)` is more precise. |
| **`void main()`** | ❌ No | **Avoid**. Non-standard and potentially dangerous. |

**Best Practice**: Always use **`int main(void)`** for simple programs and return `0` at the end to signal success

[1](https://stackoverflow.com/questions/204476/what-should-main-return-in-c-and-c)
[2](https://www.geeksforgeeks.org/c/main-function-in-c/)
[3](https://www.geeksforgeeks.org/c/c-function-argument-return-values/)
[4](https://eng.libretexts.org/Courses/Delta_College/C___Programming_I_(McClanahan)/10:_Functions/10.05:_Function_Return_Types)
[5](https://www.reddit.com/r/C_Programming/comments/1acrqc2/function_return_type_parameters_hello_world/)
[6](https://www.w3schools.com/cpp/cpp_function_return.asp)
[7](https://users.cs.utah.edu/~germain/PPS/Topics/C_Language/c_functions.html)
[8](https://www.reddit.com/r/C_Programming/comments/1cnb25k/beginner_is_the_return_type_declaration_for_a/)
[9](https://www.reddit.com/r/cs50/comments/ohkrvo/help_me_understand_what_exactly_int_main_and/)
[10](https://www.youtube.com/watch?v=CBfhcRQVpf8)



## ==================================================================================================================