package com.pevs;
import org.json.*;
/*
Using org.json external library (only in this class),
license included in the package.
*/
public class JsonToHtmlDto {
    public static String convert(String inputJson) throws Exception {
        var result = new StringBuilder("<html><table><font color=#FF751A><tr><td>Song Name<td>Album<td>Author</font>");

        var message = new JSONObject(inputJson).getJSONObject("message");
        var messageHeader = message.getJSONObject("header");
        var status = messageHeader.getInt("status_code");
        if (status != 200) throw new Exception("API Request failed with Error: " + Integer.toString(status));

        var messageBody = message.getJSONObject("body");
        var tracks = messageBody.getJSONArray("track_list");
        if (tracks.isEmpty()) return("Not Found!");
        for (int i = 0; i < tracks.length(); i++) {
            var track = tracks.getJSONObject(i).getJSONObject("track");
            var name = track.getString("track_name");
            var author = track.getString("artist_name");
            var album = track.getString("album_name");
            var color = (i%2 == 0) ? "#3D3D3D" : "#2D2D2D";
            result.append("<tr bgcolor=" + color + "><td>").append(name).append("<td>")
                    .append(album).append("<td>").append(author);
        }

        result.append("</table><html>");
        return result.toString();
    }
}
