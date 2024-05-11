#include "../Controllers/ViewController.h"
#include "../Controllers/BookController.h"

#pragma once

int reportsShownCount;
int reportVisiblesCount;
int reportScrollPos = 0; 

void UpdateReportScrollBar(HWND hwnd) {
    SCROLLINFO reportSi;
    reportSi.cbSize = sizeof(reportSi);
    reportSi.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    reportSi.nMin = 0;
    reportSi.nMax = 4 * reportsShownCount - 3 * reportVisiblesCount;
    reportSi.nPage = reportVisiblesCount;
    reportSi.nPos = reportScrollPos;
    SetScrollInfo(ReportScrollbar, SB_CTL, &reportSi, TRUE);
}

void InitializeReportLabels(HWND hwnd){
    int yPos = 50;
    // char info[100];
    for (int i = 0; i < reportsShownCount; ++i) {
        // strcpy(info, "");

        // strcat(info, reports[i]);
        ReportListLabel[i] = CreateWindow("STATIC", reports[i], WS_CHILD | WS_VISIBLE, 110, yPos, 1000, REPORT_HEIGHT, hwnd, (HMENU)(IDC_REPORT_INFO_ID0 + i), NULL, NULL);
        yPos += REPORT_HEIGHT;
    }
}

void UpdateReportLabels(HWND hwnd) {
    int yPos =  -reportScrollPos * REPORT_HEIGHT;
    for (int i = 0; i < reportsShownCount; ++i) {
        SetWindowPos(ReportListLabel[i], NULL, 110, yPos, 1000, REPORT_HEIGHT, SWP_NOZORDER);
        yPos += REPORT_HEIGHT + 40;
    }
}

void UpdateReportView(HWND hwnd){
    UpdateReportScrollBar(hwnd);
    UpdateReportLabels(hwnd);
    UpdateWindow(hwnd);
}

void ShowReportView(HWND hwnd){
    reportsShownCount = reportsCount;

    InitializeReportLabels(hwnd);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    reportVisiblesCount = clientRect.bottom / REPORT_HEIGHT;
    ReportLabel = CreateWindow("STATIC", "Reports", WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hwnd, (HMENU)IDC_REPORT_LABEL, NULL, NULL);
    ReportToAdminButton = CreateWindow("BUTTON", "Back to admin", WS_CHILD | WS_VISIBLE, 0, 640, 100, 40, hwnd, (HMENU)IDC_REPORT_TOADMIN_BUTTON, NULL, NULL);
    ReportScrollbar = CreateWindow("SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_VERT, clientRect.right - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, clientRect.bottom, hwnd,  (HMENU)IDC_REPORT_SCROLLBAR, NULL, NULL);

    UpdateReportView(hwnd);
}
