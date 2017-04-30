using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Number_of_Integer_Pairs {

    abstract class NumberOfPairs {

        private static void updateMap(Dictionary<int, int> map, int keyUpdate) {
            if (!map.ContainsKey(keyUpdate)) {
                map.Add(keyUpdate, 1);
            }
            else {
                map[keyUpdate]++;
            }
        }

        public static string find(int[] array, int target) {
            Dictionary<int, int> map = new Dictionary<int, int>();
            string result = "";
            int numPairs = 0;
            for (int i = 0; i < array.Length; i++) {
                if (map.ContainsKey(array[i])) {
                    string ans = "[" + array[i] + "," + (target - array[i]) + "]";
                    for (int index = 0; index < map[array[i]]; index++) {
                        //Console.WriteLine(ans);
                        numPairs++;
                        result += ans + " , ";
                    }
                }
                updateMap(map, target - array[i]);
            }
            return numPairs.ToString() + "\t" + result;
        }
    }

    abstract class RandomNumber {
        public static int[] createRandomArrays(int n,int rangeStart,int rangeEnd) {
            if (rangeStart > rangeEnd) return null;
            Random rnd = new Random();
            int[] array = new int[n];
            for (int i = 0; i < n; i++) {
                array[i] = rnd.Next(rangeStart, rangeEnd + 1);
            }
            return array;
        }
    }

    class main {
        static void Main(string[] args) {

            //============================= init
            int n = 10;
            int[] array = RandomNumber.createRandomArrays(n,1,500);//{ 1,1,3,3,3,7,7,9,10,11 };

            string head = "[";
            foreach(int i in array) {
                head += i + ",";
            }
            head += "]" +Environment.NewLine;

            //============================= find Number of pairs
            string result = "Target\t#pairs\tPairs" + Environment.NewLine;
            for (int i = 500; i <= 1000; i++) {
                result += i.ToString() + "\t" + NumberOfPairs.find(array, i) + Environment.NewLine;
            }


            //============================= write file
            string path = "Example.txt";
            System.IO.File.Create(path).Dispose();
            using (System.IO.TextWriter tw = new System.IO.StreamWriter(path)) {
                tw.Write(head);
                tw.Write(result);
                tw.Close();
            }
        }
    }
}