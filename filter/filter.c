#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/fcntl.h>
#include <linux/version.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Filter module");
MODULE_AUTHOR("John Harvey");

void fileread(const char * filename)
{
  // Create variables
  struct file *f;
  char buf[128];
  mm_segment_t fs;
  size_t bytes;
  int i;
  int t;
  // Initiate buffer
  for(i=0;i<128;i++)
      buf[i] = 0;
  // print to dmesg to see its loaded
  printk(KERN_INFO "My module is loaded\n");

  // open test file, which is textfile.txt
  f = filp_open("textfile.txt", O_RDONLY, 0);
  if(f == NULL)
      printk(KERN_ALERT "filp_open error!!.\n");
  else{
      // Get current segment descriptor
      fs = get_fs();
      // Set segment descriptor associated to kernel space
      set_fs(get_ds());
      // Read the file
      f->f_op->read(f, buf, 128, &f->f_pos);

      //make filter changes
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

}

int init_module()
{
  char *filename="textfile.txt";

  printk("read file from kernel\n");
  fileread(filename);
  return 0;
}

void cleanup_module()
{
  printk("module unloaded\n");
}
