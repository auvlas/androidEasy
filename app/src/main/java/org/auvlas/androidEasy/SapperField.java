package org.auvlas.androidEasy;

import android.content.Context;
import android.util.AttributeSet;

public class SapperField extends Grid {
    public SapperField(Context context, AttributeSet attr) {
        super(context, attr);
    }

    public void setParams(
            long rows, long cols, long mins, long radiusMins) {
        setMap(new MinsField(rows, cols, mins, radiusMins));
    }

    public void setVictoryCallback(OnClickListener victoryCallback) {
        ((MinsField) getMap()).setVictoryCallback(victoryCallback);
    }

    public void setDefeatCallback(OnClickListener defeatCallback) {
        ((MinsField) getMap()).setDefeatCallback(defeatCallback);
    }
}
