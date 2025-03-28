"""
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，
并返回移除后数组的新长度。
"""


class Solution1 :
    def remove_elements(self, nums, val):
        #快慢指针
        fast = 0
        slow = 0
        size =  len(nums)
        while fast < size:
             if nums[fast] != val:
                 nums[slow] = nums[fast]
                 slow += 1
             fast += 1
        return slow


#二分查找
class Solution2 :#左闭右闭
    def Binarysearch1(self,nums,val):
        left,right = 0 , len(nums)-1

        while left <= right:
            mid = (left + right) // 2

            if nums[mid]<val:
                left = mid + 1
            elif nums[mid]>val:
                right = mid - 1
            else:
                return mid
        return -1 #没有找到

class Solution3:#左闭右开
    def BinarySearch2(self,nums,val):
         left,right = 0,len(nums)

         while left < right:
             mid = (left + right) // 2
             if nums[mid] > val:
                 right = mid
             elif nums[mid] < val:
                 left = mid + 1
             else:
                 return mid
         return -1


class Solution4:#有序数组的平方
    def sortedSquares(self,nums):
        left,right = 0,len(nums)-1
        result = []
        while left <= right:
            if abs(nums[left]) < abs(nums[right]):
                result.append(abs(nums[right]))
                right -= 1
            else:
                result.appned(abs(nums[left]))
                left -= 1
        return result[::-1]
