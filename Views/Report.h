#include "../Repositories/ViewRepository.h"
#include "../Repositories/BookRepository.h"

#pragma once

int reportsCount;
int reportVisiblesCount;
int reportScrollPos = 0; 

void UpdateReportScrollBar(HWND hwnd) {
    SCROLLINFO reportSi;
    reportSi.cbSize = sizeof(reportSi);
    reportSi.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    reportSi.nMin = 0;
    reportSi.nMax = 4 * reportsCount - 3 * reportVisiblesCount;
    reportSi.nPage = reportVisiblesCount;
    reportSi.nPos = reportScrollPos;
    SetScrollInfo(ReportScrollbar, SB_CTL, &reportSi, TRUE);
}

void InitializeReportLabels(HWND hwnd){
    int yPos = 50;
    for (int i = 0; i < reportsCount; ++i) {
        ReportsListLabel[i] = CreateWindow("STATIC", reports[i], WS_CHILD | WS_VISIBLE, 110, yPos, 150, REPORT_HEIGHT, hwnd, (HMENU)(IDC_REPORT_INFO_ID0 + i), NULL, NULL);
        yPos += 2 * REPORT_HEIGHT;
    }
}

void UpdateReportLabels(HWND hwnd) {
    int yPos =  -reportScrollPos * REPORT_HEIGHT;
    for (int i = 0; i < reportsCount; ++i) {
        SetWindowPos(ReportsListLabel[i], NULL, 110, yPos, 150, REPORT_HEIGHT, SWP_NOZORDER);
        yPos += 2 * REPORT_HEIGHT + 40;
    }
}

void UpdateAdminView(HWND hwnd){
    UpdateReportScrollBar(hwnd);
    UpdateReportsLabels(hwnd);
    UpdateWindow(hwnd);
}

void ShowReportView(HWND hwnd){
    reportsCount = reportsCount;

    InitializeReportLabels(hwnd);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    reportVisiblesCount = clientRect.bottom / REPORT_HEIGHT;
    ReportsLabel = CreateWindow("STATIC", "Reports", WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hwnd, (HMENU)IDC_REPORTS_LABEL, NULL, NULL);
    ReportToLoginButton = CreateWindow("BUTTON", "Back to admin", WS_CHILD | WS_VISIBLE, 0, 640, 100, 40, hwnd, (HMENU)IDC_REPORT_TOADMIN_BUTTON, NULL, NULL);
    ReportScrollbar = CreateWindow("SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_VERT, clientRect.right - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, clientRect.bottom, hwnd,  (HMENU)IDC_REPORT_SCROLLBAR, NULL, NULL);

    UpdateReportView(hwnd);
}
