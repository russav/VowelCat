#include <dirent.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "jkFormant.h"

int main() {
    struct stat st;
    int fd;
    void *mem;

    fd = open("out.raw", O_RDONLY);
    fstat(fd, &st);
    mem = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);

    Tcl_Obj obj = {
        .bytes = (char *)(&((short *)(mem))[0]),
        .len = st.st_size,
    };

    Sound *s = Snack_NewSound(44100, LIN16, 2);
    LoadSound(s, &obj, 0, 44100);

    formantCmd(s);

    Snack_DeleteSound(s);
}
