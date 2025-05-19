齊						x + y										                                # Anal Add						  0x2FD1	    even
隶						x - y										                                # Anal Subtract			 0x2FAA		    slave
丶 						x * y										                                # Anal Multiply			 0x2F02		    dot
丿 						x / y if y != 0 else float('inf')		# Anal Divide			    ox2F03		   slash
而						min(x, y)									                           # Anal AND					   0x2F7D		   and
或						max(x, y)									                           # Anal OR						 0x6216		     or
⊕						abs(x - y)									                        # Anal XOR (Rule 90 style)		0x2295	direct sum/exclusiveOR  (XOR)
无						-x,		 									                                    # Anal NOT						0x2F46			not
无‍而				  -(min(x, y)						                                  # Anal NAND	0x2F46-0x200D-0x2F7D    not-and
无‍或				  -(max(x, y)						                                  # Anal NOR	0x2F46-0x200D-0x6216	  not-or
若					     if x>0										                                # Ana IF						0x82E5		        if
则					     then y										                                # Anal THEN					0x5219		  (if...)then
另					     else z										                                # Anal ELSE					0x53E6		   other
門					     y ← x										                                    # Anal Assignment 0x2FA8		 gate
大				         x > y										                                    # Anal Greater Than	0x2F24	    big
小				         x < y										                                    # Anal Less Than      0x2F29		 small
卜					     x == y										                                   # Anal Equals			0x2F22			divination
丨					     x != y										                                   # Anal Does Not Equal	0x2F18	line
走					     x >= y										                                   # Anal Gtr Than Or Equal0x2F9Brun
夊					     x <= y										                                   # Anal Less Than Or Equal0x2F21slowly
老					    (while)									                                    # while						   0x2F7C		    old
至					    (for)										                                    # for						0x2F84			arrive
舛					    (except)									                             # except						0x2F87			oppose
自					    (define)							                            		# define						0x2F7D	 		self
又					    (return)								                               	# return						0x2F1C			again
入					    (x in list)									                            # in								  U+5165			in
止					    (break)							                                    		# break							0x2F4C		stop	 
出					     print or output)							                    # out							   U+51FA			out	
氏/ 谷			    (int x or uint x)							                    # int/# uint	0x2F52/0x2F95	clan/valley 
己					    (str x)			                                    							# str					       	 0x2F30	oneself	
辵					    (const x)									                                # const						  0x2FA1    walk
比					    (bool x)									                               	# bool					          x2F50			compare
終					    (end)								                                    		# end						     U+7D42		    end
響					    (echo x)								                            		# echo							U+97FF		   echo
釆					    (doen)								                                   		    # done						0x2ED4			stand
卩					    (exit)									                                    	# exit						   U+5369	seal/go out
押					    (prompt x)									                                # prompt				   U+62BC		  push
支					    (count x)								                                	# count						   B0x2F40		branch
⽰					    (input x)								                                	# input						   U+2F70	spirit		
眠					    (sleep)									                                    	# sleep						  U+7720		drowsy
⺒					    (http)									                                    	# http							 U+2E92	    snake
⺨					    (proxy)									                                	# proxy							   U+2EA8		 dog
⽪					    (user_agent)			                            					# user_agent		 U+2F6A		   skin
⽓					    (server)							                                		# server					    U+2F53		 steam
待					    (wait)								                                    		# weit							 U+5F85	   wait	
⻤					    (null)							                                    			# null							 U+2EE4	      ghost
⺙					    (pront)								                                   		# print							   U+2E99		 rap
⺆					    (sys_call)							                            		# sys_call					U+2E86		  box	
⺘					    (function)								                            	# fnct								U+2E98		 hand
工					    (move)										                                    # mov						0x2F2F			work
⺣					    (att)										                                    # attribute					U+2EA3		fire	
巡					   (for x in range)						                           	# loop								 U+5DE1		   patrolling
非					   (err)									                                    	# error							 0x2FAE		wrong
道					   (path)								                                       		# path							 U+9053			way
⺢					   (type x)								                                   		# type								U+2EA2		water
字					   (char)							                                    			# char						     U+5B57		roof+child
読					   (read x)				    		            	                            	# read						    U+8AAD		read
艮					    (net)							                                               	# net							 0x2F79	net		
⻔					    (gate)			                                            					# gate							0x2FA4		gate
1					    (one)								                                            	# 1										    one
2					    (two)						                                                   		# 2										two
3					    (three)							                                            	# 3											three
4					    (four)					    		                                            # 4											four
6					    (five)						                                                		# 5										five
7					    (six)								                                               	# 6									    six
8					    (seven)						                                                	# 7											seven
9					    (eight)								                                            # 8											eight
0					    (nine)							                                                    # 9										nine
q					    (Q)	    							                                               		# 0										Q
w					    (W)		    								                                            # q									    W
e					    (E)			    						                                              	# w									    E
r					    (R)				        				                                               	# e										R
t					    (T)						    	                                        				# r										T
y					    (Y)						                                        	    				# t										Y
u					    (U)								                                            			# y										U
i					    (I)								                                        	    		# i										I
o					    (O)										    	                                        # o										O
p					    (P)						                                        					    # p										P
a					    (A) 									                                           		# s	    								A
s					    (S)	    									                                           	# d										S
d			            (D)		    			                                        						# f										F
g					    (G)			    				                                        				# g									    G
h					    (H)				    					                                        		# h										H
j					    (J)					    				                                        		# j										J
k					    (K)						    	                                        				# k										K
l					    (L)							                                            				# l										L
z					    (Z)								    			                                        # z										Z
x					    (X)									    	                                        	# x										X
c					    (C)										                                             	# c										C
v					    (V) 							                                           				# v										V
b					    (B)	    						                                        				# b										B
n					    (N)		        			                                        					# n										N
m					    (M)				    					                                           		# m										M
[					    ([)					    	                                        					# [										LSB
]					    (])						    	                           				                # ]										RSB
(					    (()							    			                                        	# (										LCB
)					    ())								    		                                    	    # )								   	    RCB
_					    (_)				                                        					    		# _									    U_S
'   				      (')									    		                                        # '								    Ap'
