/*
 * memory.c
 *
 *  Created on: Apr 20, 2013
 *      Author: niltonvasques
 */

#include <types.h>
#include <kheap.h>

#define USER_MEMORY_INIT  	0x1000000
#define KERNEL_MEMORY_INIT 	0x100000

//extern u32int end;
u32int placement_address = KERNEL_MEMORY_INIT;


u32int kmalloc( u32int sz ){
	int tmp = placement_address;
	placement_address += sz;
	return tmp;
}

u32int kmalloc_a(u32int sz)  // page aligned.
{
  if (placement_address & 0xFFFFF000) // If the address is not already page-aligned
  {
    // Align it.
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  int tmp = placement_address;
  placement_address += sz;
  return tmp;
}

u32int kmalloc_p(u32int sz, u32int *phys) // returns a physical address.
{
	if(phys){
		*phys = placement_address;
	}

	u32int tmp = placement_address;
	placement_address += sz;
	return tmp;

}

u32int kmalloc_ap(u32int sz, u32int *phys) // page aligned and returns a physical address.
{
  if (placement_address & 0xFFFFF000) // If the address is not already page-aligned
  {
    // Align it.
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  if (phys)
  {
    *phys = placement_address;
  }
  u32int tmp = placement_address;
  placement_address += sz;
  return tmp;
}




