# <p align = "center"> LZW Compression with a Parallelizable Approach </p>
<p align = "center"> By Ben Potter, Jake Kirkman, Zach Kunzer, and Justin Grage </p>

## Abstract 

  We wanted to experiment with compression algorithms, specifically LZW (Lempel–Ziv–Welch), and how they’re used in data compression. For our main problem that we will solve, we have chosen that text compression would be best suited for a parallelizable approach and as a clear demonstration of such. We chose LZW over Huffman because we believed that Huffman cannot be parallelizable as well as LZW in practice for the problem of text compression. We will employ uses of OpenMP functions to achieve this parallel approach. We believe that the expected outcomes will result in a faster elapsed time to complete larger subsets of text data, while it will result in slower times with smaller subsets of text data.  


## Problem Description 

  According to reference [Maulunida, R. and Solichin, A.], compression algorithms fall into one of two categories: lossy and lossless. Lossy describes compression algorithms in which there is a potential to lose data in the act of compression or decompression. The antithesis to lossy is lossless where there is no data loss while compressing or decompressing. Lossless compression algorithms are ideal for their reliability. The LZW algorithm our group is focusing our attention on is a lossless compression algorithm. 

Since LZW is a lossless compression algorithm, it has a wide array of various applications including gif, pdf, txt, and tiff compression [GeeksforGeeks]. For the project this semester, we’re planning to focus on txt compression as a proof of concept. We found a website called Project Gutenberg which has text files of classic literature books that reached public domain. These classic novels will serve as a great ‘stress test’ for the LZW algorithm. 

The idea of LZW compression is a dictionary-based approach to compression much like other algorithms like Huffman Code. However, according to [Klein, S.T. and Wiseman, Y.], Huffman Code requires the sender to distribute the encoding table alongside the compressed file. A benefit to LZW is it doesn’t need to send an encoding table. The decompression can operate with just the raw data. 

The LZW algorithm has two sections, compression and decompression. In this semester project, these are the problems we’re going to have to try and solve. How the LZW compression works is by reading a file character by character and filling it into our dictionary along size a number. It will then go through with multiple characters in a string and fill those sections into the table. This process will be repeated until the entire file can be represented through a series of code numbers. In the simplest terms possible, the decompression algorithm will reverse this technique which is how it’s able to compile without a translation key [GeeksforGeeks]. 

The following image comes from reference [GeeksforGeeks] and shows a great example of how the compression algorithm works:
![Image](https://github.com/user-attachments/assets/092b4ac9-97d9-40e1-9e2f-9c570a2df22a)

Both the compression and decompression aspects of the algorithm can benefit from parallelism. It is important because processing time can be significant when dealing with large amounts of data. It is especially important that algorithms are able to utilize the multicore design of modern systems. Managing dependencies is a key area for parallelizing LZW. It relies on generating a code table that is read and modified as input data is processed. To parallelize LZW, a straightforward strategy would be to divide the data into chunks and have each thread maintain its own code table.  

To have a good balance of compression rate and speed, a certain level of dependency (accessing code table of other threads) and chunk size should be chosen. Smaller chunk sizes could result in more efficient usage of multiple cores, but the code tables for each thread would be less robust due to having less information to build codes from which results in a lower compression rate. More data sharing could help the problem, but this would result in higher synchronization. Overall, a balance is needed to parallelize efficiently. 

From GeeksForGeeks: 
![Image](https://github.com/user-attachments/assets/f3ba3f8b-784d-4422-a4c4-98113e71522f)

From the scholarly article, “Parallel Lempel Ziv coding”: 

![Image](https://github.com/user-attachments/assets/a6536ce3-df0f-4bfc-aad8-cd5df97a8c6a)


## Intellectual Challenge 

  LZW compression algorithm has multiple aspects which makes this compression difficult to parallelize. When writing a LZW compression algorithm, it’s important to focus on both encoding and decoding as encoded messages don’t serve much purpose without a way to read them. 

Both encoding and decoding have similar challenges when parallelizing the algorithm. When encoding, one of the easier challenges is setting up parallel program and giving each thread their own section of text to encode [Funasaka, S., Nakano, K., and Yasuaki, I]. However, the major roadblock we might face with this algorithm is ensuring that parallel threads don’t try to save into the same entry on the table. As we know previously with LZW encoding, an LZW algorithm will traverse character/characters at a time checking an encoding table if that character(s) is currently saved and if not if will add it to the encoding table. The problem occurs when we split our text up. The issue arises due to splitting the original text file up between multiple files. Now when saving to the encoding table the entries will be mixed up and out of order then they normally would be when going sequentially. 

LZW decoding has a very similar issue as to encoding. The LZW compression algorithm doesn’t require the sender to transfer the encoding table like other algorithms like Huffman. Due to this the decoding algorithm needs to build the decoding table as it reads through the encoded file. Similarly to encoding the easy part is splitting up the encoded message through parallel threads to decode them but like with encoding, this raises a potential issue of building a table out of order. 

Given by the paper [Klein, S.T. and Wiseman, Y.], we know that LZW compression is possible to parallelize however as stated there will be a few challenges to overcome when parallelizing this algorithm.  


## Resources 

  For our resources, we plan to use existing pieces of code and pseudocodes as inspiration for the main problem. It won’t be a complete 1-to-1 copy of those code snippets, but they will be used as references for us to navigate how to build the sequential version.  

Our major sources of background information come from the articles from [GeeksForGeeks] and [Maulunida, R. and Solichin, A.] that elegantly explain the description, use, and implementation of LZW encoding. We are also using scholarly articles from [Funasaka, S., Nakano, K., and Yasuaki, I.] and [Klein, S.T. and Wiseman, Y.] that delves into ways that a LZW encoding can be parallelized. For pseudocodes, we are working mainly with the two as shown from the problem description

## References 

Funasaka, S., Nakano, K., and Yasuaki, I. (no date) A Parallel Algorithm for LZW decompression, with GPU implementation. Available at: https://www.cs.hiroshima-u.ac.jp/cs/_media/cp14.pdf (Accessed: 22 March 2025). 

Klein, S.T. and Wiseman, Y. (2004) Parallel lempel ziv coding, Parallel Lempel Ziv coding. Available at: https://www.sciencedirect.com/science/article/pii/S0166218X04003476?ref=pdf_download&fr=RR-2&rr=922f11cfd998e10c#sec1 (Accessed: 21 March 2025). 

LZW (Lempel–Ziv–Welch) compression technique (2024) GeeksforGeeks. Available at: https://www.geeksforgeeks.org/lzw-lempel-ziv-welch-compression-technique/ (Accessed: 21 March 2025). 

Maulunida, R. and Solichin, A. (2018) Optimization of LZW Compression Algorithm With Modification of Dictionary Formation. Available at: https://www.researchgate.net/publication/322890646_Optimization_of_LZW_Compression_Algorithm_With_Modification_of_Dictionary_Formation (Accessed: 22 March 2025). 
