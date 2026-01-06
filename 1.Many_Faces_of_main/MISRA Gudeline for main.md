The MISRA C guidelines (specifically MISRA C:2012) have specific rules and directives that apply to the `main` function to ensuring safety, portability, and predictability in embedded systems.

### 1. Return Type and Parameters (Rule 8.4 Exception)
MISRA C generally requires all global functions to have a separate prototype declaration. However, **`main` is an exception**.
*   **Rule 8.4**: A compatible declaration shall be visible when an object or function with external linkage is defined.
    *   **Exception**: The function `main` does not need a separate prototype declaration because it is the entry point defined by the environment.[1]
*   **Definition**: The definition should still follow standard C. While MISRA doesn't explicitly ban `int main(void)` vs `int main(int argc, char *argv[])`, it enforces standard compliance. Therefore, you should use `int main(void)` if you don't use arguments, to avoid unused parameter violations.

### 2. Uniqueness (Rule 6.0.4 - Required)
*   The identifier `main` **must not be used** for any function other than the global entry point.[2]
*   You cannot create a helper function called `main` inside a library or another module. There must be exactly one `main`.

### 3. Return Statement (Rule 17.4 - Mandatory)
*   **Rule 17.4**: All exit paths from a function with a non-void return type shall have an explicit `return` statement with an expression.[2]
*   **Application to `main`**: Since `main` returns `int`, you **must** explicitly write `return 0;` (or another integer) at the end of the function. Relying on the C99 feature where `main` implicitly returns `0` is a violation of this rule.

### 4. No Recursive Calls (Rule 17.2 - Required)
*   **Rule 17.2**: Functions shall not call themselves, either directly or indirectly.
*   **Application to `main`**: You are strictly prohibited from calling `main()` recursively from within your program. This prevents stack overflow and undefined behavior risks.

### Summary Checklist for MISRA Compliant `main`

| Feature | MISRA Compliant Approach |
| :--- | :--- |
| **Declaration** | No separate prototype required (Rule 8.4 Exception). |
| **Definition** | `int main(void)` (preferred for embedded). |
| **Return** | Must have explicit `return 0;` at the end (Rule 17.4). |
| **Usage** | Identifier `main` cannot be used elsewhere (Rule 6.0.4). |
| **Recursion** | Never call `main()` inside your code (Rule 17.2). |

**Example of MISRA Compliant Main:**
```c
/* No prototype needed for main */

int main(void) {
    /* ... system initialization ... */
    
    /* ... main application loop ... */
    
    return 0; /* Mandatory explicit return */
}
```

[1](https://forum.misra.org.uk/showthread.php?tid=1237)
[2](https://www.blackduck.com/static-analysis-tools-sast/misra.html)
[3](https://en.wikipedia.org/wiki/MISRA_C)
[4](https://ldra.com/misra/)
[5](https://misra.org.uk/app/uploads/2021/06/MISRA-C-2012-AMD2.pdf)
[6](https://pvs-studio.com/en/pvs-studio/sast/misra/)
[7](https://www.mathworks.com/help/bugfinder/misra-c-2023-reference.html)
[8](https://www.perforce.com/resources/qac/misra-c-cpp)
[9](https://www.parasoft.com/solutions/misra/)
[10](https://community.sonarsource.com/t/misra-c-c-rules-implemented/132964)