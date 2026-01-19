# Guide to Running Solidity Assignments in Remix

## Step 1: Setup
1.  Open [Remix IDE](https://remix.ethereum.org/).
2.  On the left sidebar, click the **File Explorers** icon (top one).
3.  Create a new file (e.g., `Bank.sol`) and paste the Assignment 3 code.
4.  Create another file (e.g., `Student.sol`) and paste the Assignment 4 code.

## Step 2: Compile
1.  Click the **Solidity Compiler** icon on the left (3rd one down).
2.  Ensure the `Compiler` version matches the one in your code (e.g., 0.8.x).
3.  Click the blue **Compile** button. Verify you see a green checkmark on the compiler icon.

## Step 3: Deploy & Run (Assignment 3 - Bank)
1.  Click the **Deploy & Run Transactions** icon on the left (4th one down).
2.  **Environment:** Select `Remix VM (Cancun)` (this is your simulator).
3.  **Contract:** Select `SimpleBank` from the dropdown menu.
4.  Click **Deploy**.
5.  Expand your contract under "Deployed Contracts" at the bottom left.
    * **To Deposit:**
        * Set **Value** (top of panel) to `1` and change unit to `Ether`.
        * Click the red `deposit` button.
        * *Check console for green tick.*
    * **To Show Balance:**
        * Click the blue `getBalance` button. It will show the balance in Wei (e.g., 1 ETH = `1000000000000000000` Wei).
    * **To Withdraw:**
        * Enter amount in **Wei** in the `withdraw` box (e.g., `500000000000000000` for 0.5 ETH).
        * *Exam Tip: Deposit 100 Wei, then withdraw 50 Wei to keep it simple.*

## Step 4: Deploy & Run (Assignment 4 - Student)
1.  Clear previous deployments (trash icon near "Deployed Contracts").
2.  Select `StudentRegistry` contract and click **Deploy**.
3.  Expand the deployed contract.
    * **Add Student:** Enter `1, "John", 20` next to the `addStudent` button and click it.
    * **Check Array:** Enter `0` into the blue `students` button to view the first student.
    * **Test Fallback:**
        * Go to "Low level interactions" at the bottom.
        * Ensure **Value** has some Ether (e.g., 1 Ether).
        * Click **Transact** (triggers `receive`/`fallback`).

## How to Observe Gas & Transaction Fees (Required for Q4)
After clicking any orange/red button (e.g., `addStudent`, `deposit`):
1.  Look at the **black console window** at the bottom.
2.  Click the down arrow `v` next to the green checkmark transaction line.
3.  Show the examiner the **"gas"**, **"transaction cost"**, and **"execution cost"** fields.