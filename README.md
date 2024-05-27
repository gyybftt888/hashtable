# hashtable
有個檔案 ( dict.txt, 約 1.07 MB ) 內含約 68,000 個英文字以及相對應的數值 (integer)，要建立一個 hash table 提供未來查詢使用。

>例如：  
aa 0  
ab 1  
ac 0  
…  

(資料結構是標準的 hash table，有 header，後面用 linked-list 串起來，採用 linked-list 來解決 collision 的問題)

舉例說明：
當查詢 aa 時，可以找到相對應的數值 => 0
( dict.txt 的資料中有 aa 0 這筆資料)

實作下列兩個 Library Function：
1. build_hash : 將所指定的檔案建構出一個 hash table，檔案格式如上。
2. query_hash : 查詢所指定英文字的資料，回傳其相對應數值。
