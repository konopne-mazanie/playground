package com.pevs;

import java.io.*;
import java.net.*;

public class Api {
    public static final String API_KEY = "3968cc7ac24419a70ea83a6ae07deea4";
    public static String getSong(String searchTerm) throws Exception {
        var result = new StringBuilder();
        var url = new URL("http://api.musixmatch.com/ws/1.1/track.search?apikey=" + API_KEY + "&q="
                + searchTerm.replace(" ", "%20").replace("\n", "%20"));
        var conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        var reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            result.append(line);
        }
        reader.close();
        return result.toString();
    }
}
