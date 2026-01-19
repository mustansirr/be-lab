// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentRegistry {

    // 1. Structure to hold student data
    struct Student {
        uint256 id;
        string name;
        uint256 age;
    }

    // 2. Array to store multiple students
    Student[] public students;

    // Function to add a new student to the array
    function addStudent(uint256 _id, string memory _name, uint256 _age) public {
        students.push(Student(_id, _name, _age));
    }

    // Function to get total number of students
    function getTotalStudents() public view returns (uint256) {
        return students.length;
    }

    // 3. Fallback function
    // This function is called if someone sends Ether without specifically calling 'addStudent'
    // or calls a function that doesn't exist.
    fallback() external payable {
        // You can leave this empty, it just needs to exist to satisfy the requirement.
        // It allows the contract to accept Ether even if no valid function is called.
    }

    // Optional: Good practice to have receive() alongside fallback() for just plain Ether transfers
    receive() external payable {}
}