package org.auvlas.androidEasy;

import android.view.View;
import android.view.View.OnClickListener;

public class MinsField implements Grid.Map, AutoCloseable {
    private long m_nativePtr = 0;
    private OnClickListener m_victoryCallback = null;
    private OnClickListener m_defeatCallback = null;
    private View m_view = null;

    public MinsField(long rows, long cols, long mins, long radiusMins) {
        init(rows, cols, mins, radiusMins);
    }

    @Override
    public synchronized void close() {
        if (m_nativePtr != 0) {
            destroy();
            m_nativePtr = 0;
        }
    }

    protected void finalize() throws Throwable {
        try {
            close();
        } finally {
            super.finalize();
        }
    }

    public OnClickListener getVictoryCallback() {
        return m_victoryCallback;
    }

    public void setVictoryCallback(OnClickListener victoryCallback) {
        m_victoryCallback = victoryCallback;
    }

    public OnClickListener getDefeatCallback() {
        return m_defeatCallback;
    }

    public void setDefeatCallback(OnClickListener defeatCallback) {
        m_defeatCallback = defeatCallback;
    }

    public View getView() {
        return m_view;
    }

    public void setView(View view) {
        m_view = view;
    }

    private native void init(long rows, long cols, long mins, long radiusMins);

    public native long getMins();
    public native byte getMins(long row, long col);

    public native boolean getMin(long row, long col);

    public native void setUpFlag(long row , long col);

    public native void setDownFlag(long row , long col);

    public native boolean getFlag(long row, long col);

    public native long getRows();

    public native long getCols();

    public native long getSize();
    public int click(long row, long col) {
        boolean isDefeat = getOpen(row, col);

        if (isDefeat && null != m_defeatCallback && null != m_view) {
            m_defeatCallback.onClick(m_view);
        } else {
            boolean isVictory = getVictory();

            if (isVictory && null != m_victoryCallback && null != m_view) {
                m_victoryCallback.onClick(m_view);
            }
        }

        return isDefeat ? 0 : 1 + getMins(row, col);
    }

    public native long getEmpty();

    public native long getEmptyOpen();

    public native long getEmptyClose();

    public native float getVictoryPerfect();

    public native boolean getLive();

    public native boolean getVictory();

    public native void setOpen(long row, long col);

    public native boolean getOpen(long row, long col);

    private native void destroy();
}