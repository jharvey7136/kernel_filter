#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

#include "sysfilter.h"


asmlinkage long sys_filter(void) {
  struct file *f;
  char buf[128];
  mm_segment_t fs;
  int i;

  for(i=0;i<128;i++)
      buf[i] = 0;

  printk(KERN_INFO "My module is loaded\n");

  f = filp_open("/etc/os-release", O_RDONLY, 0);
  if(f == NULL)
      printk(KERN_ALERT "filp_open error!!.\n");
  else{
      // Get current segment descriptor
      fs = get_fs();
      // Set segment descriptor associated to kernel space
      set_fs(get_ds());
      // Read the file
      f->f_op->read(f, buf, 128, &f->f_pos);

      bytes = sizeof(buf);
      for (t = 0; t < bytes; i++){
        if (buf[i] == 101){
          buf[i] = 69;
        }
      }


      // Restore segment descriptor
      set_fs(fs);
      // See what we read from file
      printk(KERN_INFO "buf:%s\n",buf);
  }
  filp_close(f,NULL);


  return 0;
}
