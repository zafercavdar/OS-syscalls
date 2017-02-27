#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

// http://www.tldp.org/LDP/lkmpg/2.6/html/x323.html

int id = 0;
module_param(id,int,0);

struct fileinfo304 {
	size_t size;
	char filename[100];
	char datecreated[100];
	int owner_id;
	int file_id; 
	struct list_head list;
};

/**
 * The following defines and initializes a list_head object named files_list
 */

static LIST_HEAD(files_list);

int fileinfo304_init(void){
	
	struct fileinfo304 *element, *nxt;
	struct fileinfo304 *info;
	struct fileinfo304 *info2;
	struct fileinfo304 *info3;
	struct fileinfo304 *info4;
	struct fileinfo304 *info5;
	struct fileinfo304 *info6;

	struct fileinfo304 *ptr;
	int total = 0;
	int deleted = 0;

	printk(KERN_INFO "Loading Module\n");

	info = kmalloc(sizeof(*info), GFP_KERNEL);
	info->size = 10;
	strcpy(&info->filename,"Lecture Notes");
	strcpy(&info->datecreated,"27.02.2017");
	info->owner_id = 23525;
	info->file_id = 2352510;
	INIT_LIST_HEAD(&info->list);

	list_add_tail(&info->list, &files_list);

	info2 = kmalloc(sizeof(*info2), GFP_KERNEL);
	info2->size = 20;
	strcpy(&info2->filename,"Homeworks");
	strcpy(&info2->datecreated,"27.02.2017");
	info2->owner_id = 23525;
	info2->file_id = 2352520;
	list_add_tail(&info2->list, &files_list);

	info3 = kmalloc(sizeof(*info3), GFP_KERNEL);
	info3->size = 30;
	strcpy(&info3->filename,"Quizs");
	strcpy(&info3->datecreated,"27.02.2017");
	info3->owner_id = 23525;
	info3->file_id = 2352530;
	list_add_tail(&info3->list, &files_list);

	info4 = kmalloc(sizeof(*info4), GFP_KERNEL);
	info4->size = 40;
	strcpy(&info4->filename,"Previous Exams");
	strcpy(&info4->datecreated,"27.02.2017");
	info4->owner_id = 23525;
	info4->file_id = 2352540;
	list_add_tail(&info4->list, &files_list);
	
	info5 = kmalloc(sizeof(*info5), GFP_KERNEL);
	info5->size = 50;
	strcpy(&info5->filename,"Term Project");
	strcpy(&info5->datecreated,"27.02.2017");
	info5->owner_id = 23525;
	info5->file_id = 2352550;
	list_add_tail(&info5->list, &files_list);

	info6 = kmalloc(sizeof(*info6), GFP_KERNEL);
	info6->size = 60;
	strcpy(&info6->filename,"Codes");
	strcpy(&info6->datecreated,"27.02.2017");
	info6->owner_id = 23525;
	info6->file_id = 2352560;
	list_add_tail(&info6->list, &files_list);

	list_for_each_entry(ptr,&files_list,list)	{
		printk(KERN_INFO "File ID: %d\n",ptr->file_id);
		printk(KERN_INFO "\tFile Name: %s\n",ptr->filename);
		printk(KERN_INFO "\tFile Owner ID: %d\n",ptr->owner_id);
		printk(KERN_INFO "\tFile Date Created: %d\n",ptr->datecreated);
		printk(KERN_INFO "\tFile Size: %zu\n",ptr->size);
	}

	list_for_each_entry_safe(element,nxt,&files_list,list){
		if (element->file_id == id){
			list_del(&element->list);
			kfree(element);
			deleted += 1;
		}
		total += 1;
	}
	printk(KERN_INFO "Number of files removed: %d\n", deleted);
	printk(KERN_INFO "Number of files remained in the list: %d\n", total-deleted);
			
	return 0;
}

void fileinfo304_exit(void) {
	struct fileinfo304 *ptr, *next;
	printk(KERN_INFO "Removing Module\n");

	list_for_each_entry_safe(ptr,next, &files_list, list){
		list_del(&ptr->list);
		kfree(ptr);
	}
}

module_init(fileinfo304_init);
module_exit(fileinfo304_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Exercise for COMP304");
MODULE_AUTHOR("Zafer Cavdar");

