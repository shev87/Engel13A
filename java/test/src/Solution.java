public class Solution {
    public static void main(String[] args) {
        String var = "<a href=\"https://tlt.ru/city/proekt-32-kvartal-poluchil-zolotuyu-medal-vserossijskogo-konkursa/2119941/\">\n" +
                "                            Проект &#171;32 квартал&#187; получил золотую медаль всероссийского конкурса\n" +
                "                        </a>\n" +
                "                    </div>";
        String[] strings = var.split("\n");
        for (String s : strings){
           // if (s.trim().matches("[А-Яа-я\\s\\W]+")){
             if (!s.trim().matches("<.+?|>|</")){
                var = s.trim();
                if (var.contains("&#171;")) var = var.replace("&#171;", "«");
                if (var.contains("&#187;")) var = var.replace("&#187;", "»");
                 System.out.println(var);
                break;
            }
        }
    }
}
