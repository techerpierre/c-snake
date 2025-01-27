## Hello from CSnake

## Compile the project

For Windows:

```bash
# without terminal
gcc -o bin/prog src/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -mwindows

# with terminal
gcc -o bin/prog-debug src/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2
```