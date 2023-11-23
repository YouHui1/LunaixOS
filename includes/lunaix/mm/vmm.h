/**
 * @file vmm.h
 * @brief Virtual memory manager
 * @author youhui
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __LUNAIX_VMM_H
#define __LUNAIX_VMM_H

#include <stdint.h>
#include <stddef.h>
#include <lunaix/mm/page.h>

/**
 * @brief 初始化虚拟内存管理器
 */
void vmm_init();

/**
 * @brief 创建一个页目录
 * @return {ptd_t*} 页目录的物理地址，随时可用加载进CR3
 */
ptd_t* vmm_init_pd();

/**
 * @brief 尝试建立一个映射关系，映射指定的物理页地址至虚拟页地址。
 *        如果指定的虚拟页地址已被占用，则尝试寻址新的可用地址
 * @param vpn  虚拟页地址
 * @param ppn  物理页地址
 * @param dattr  PDE 的属性
 * @param tattr  PTE 的属性
 * @return {void*} 虚拟页地址，不成功则为 NULL
 */
void* vmm_map_page(void* vpn, void* ppn, pt_addr dattr, pt_addr tattr);

/**
 * @brief 尝试为一个虚拟页地址创建一个可用的物理页映射
 * @param vpn  虚拟页地址
 * @param dattr
 * @param tattr
 * @return {void*} 物理页地址，不成功则为 NULL
 */
void* vmm_alloc_page(void* vpn, pt_addr dattr, pt_addr tattr);

/**
 * @brief 删除一个映射
 * @param vpn
 */
void vmm_unmap_page(void* vpn);

/**
 * @brief 获取页目录
 * @return {ptd_t*}
 */
ptd_t* get_pd();

/**
 * @brief 设置页目录
 * @param pd
 */
void set_pd(ptd_t* pd);

/**
 * @brief 将虚拟地址翻译为与其对应的物理映射
 * @param va  虚拟地址
 * @return {void*} 物理地址，映射不存在则为 NULL
 */
void* vmm_v2p(void* va);

#endif
