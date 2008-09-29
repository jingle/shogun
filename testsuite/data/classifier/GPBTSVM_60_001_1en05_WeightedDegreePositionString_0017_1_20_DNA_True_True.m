classifier_accuracy = 0.0001;
init_random = 42;
accuracy = 1e-08;
classifier_labels = [-1, -1, 1, 1, 1, -1, 1, 1, -1, -1, -1];
seqlen = 60;
classifier_tube_epsilon = 0.01;
classifier_epsilon = 1e-05;
data_test = {'CAGAAAGACTCAGATATCACGTACGGTGCTATCTAACCATACCACACTAATTACCTTTGC', 'TTGCTGTGTGCTGGAGGAAGTGAGACAAACACGCCTAGAAGGTGTAAAAGGATTCAAAAG'};
data_type = '';
kernel_name = 'WeightedDegreePositionString';
classifier_type = 'kernel';
classifier_classified = [-0.986093195, -0.985957313];
feature_type = 'Char';
classifier_C = 0.017;
name = 'GPBTSVM';
classifier_num_threads = 1;
data_train = {'TCAAGATTTCAGGTCCTCGAGAGGATGACATTTTGGCATTTGTCAGGCATGCGCCACTTC', 'TGTGGAAAATTCGCTTTCGCAAGTCTAGCAAGTCAGAGCCTCTTGAGTTCCTGCTGTGCA', 'CTGTCTCTGCGGAGAGAACGCGTGGCGGACGATGATCCAAAGCCACGGACGGACGCGTAG', 'AGCGCCATAATCGGGGAGACAGGTTTAGGCGCTTGGCTTCCATTGAAGTACGCTCTCTAG', 'AGTCAAAAGGAAAAGACAGCGGGTGGCGCACTCGCGTTCCTCCTACTGCCGACCGGACTG', 'TTTAGATTGTGCCCATAGTTGTCAACTTACAAAACTTTAATGTACATCATTTGTGTGATC', 'ATTGCGTGGCGACTAGTTCACGCAATGTACTTTTCTTAAACATTCCACGAATACTGACAC', 'ACGTCTTAGCCCCATGCACAAATTGCCGTGAAATTCATCACTCGTTACGGAGTAAGGATT', 'TGTATTCTTGCTGCAGTCCCTCAAACAGTTTAGCTCCACAGCGAGCGTGCATGAAGAGAC', 'TCCAGACCTCTACTCTCTTGCATGCGGCCTCACGCAAAGGTTTGTGGAGCTTGGAATGGT', 'TTGGTGCCATAAGAATATAGAACGTCCCATATACATCCGGTACGAGGTCCGGCGGAATGT'};
feature_class = 'string';
classifier_bias = -0.986138037089;
kernel_arg0_degree = 20;
classifier_alphas = [-0.0144278285, -0.0149227276, 0.017, 0.017, 0.017, -0.0144338025, 0.017, 0.017, -0.0146553826, -0.0126478213, -0.0139124374];
alphabet = 'DNA';
classifier_support_vectors = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
classifier_linadd_enabled = 'True';
classifier_batch_enabled = 'True';
data_class = 'dna';