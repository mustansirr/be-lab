// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract SimpleBank {

    // Mapping to hold balances for each customer address
    mapping(address => uint256) public balances;

    // 1. Deposit money
    // 'payable' allows the function to receive Ether
    function deposit() public payable {
        require(msg.value > 0, "Deposit amount must be greater than 0");
        balances[msg.sender] += msg.value;
    }

    // 2. Withdraw money
    function withdraw(uint256 amount) public {
        require(balances[msg.sender] >= amount, "Insufficient balance");
        
        // Deduct balance first to prevent re-entrancy attacks
        balances[msg.sender] -= amount;
        
        // Transfer the requested amount back to the user
        payable(msg.sender).transfer(amount);
    }

    // 3. Show balance
    // The 'public' mapping already creates a getter, but this is an explicit function if asked.
    function getBalance() public view returns (uint256) {
        return balances[msg.sender];
    }
}