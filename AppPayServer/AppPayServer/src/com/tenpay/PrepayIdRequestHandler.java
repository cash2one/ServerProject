package com.tenpay;

import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.SortedMap;
import java.util.TreeMap;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.json.JSONException;

import com.tenpay.client.TenpayHttpClient;
import com.tenpay.util.ConstantUtil;
import com.tenpay.util.JsonUtil;
import com.tenpay.util.Sha1Util;
import payserver.Log;

public class PrepayIdRequestHandler extends RequestHandler {

	public PrepayIdRequestHandler(HttpServletRequest request,
			HttpServletResponse response) {
		super(request, response);
	}

	/**
	 * 创建签名SHA1
	 * 
	 * @param signParams
	 * @return
	 * @throws Exception
	 */
	public String createSHA1Sign() {
		StringBuffer sb = new StringBuffer();
		Set es = super.getAllParameters().entrySet();
		Iterator it = es.iterator();
		while (it.hasNext()) {
			Map.Entry entry = (Map.Entry) it.next();
			String k = (String) entry.getKey();
			String v = (String) entry.getValue();
			sb.append(k + "=" + v + "&");
		}
		String params = sb.substring(0, sb.lastIndexOf("&"));
		String appsign = Sha1Util.getSha1(params);
		this.setDebugInfo(this.getDebugInfo() + "\r\n" + "sha1 sb:" + params);
		this.setDebugInfo(this.getDebugInfo() + "\r\n" + "app sign:" + appsign);
		return appsign;
	}

	// 提交预支付
	public String sendPrepay() throws JSONException {
		String prepayid = "";
		StringBuffer sb = new StringBuffer("{");
		Set es = super.getAllParameters().entrySet();
		Iterator it = es.iterator();
		while (it.hasNext()) {
			Map.Entry entry = (Map.Entry) it.next();
			String k = (String) entry.getKey();
			String v = (String) entry.getValue();
			if (null != v && !"".equals(v) && !"appkey".equals(k)) {
				sb.append("\"" + k + "\":\"" + v + "\",");
			}
		}
		String params = sb.substring(0, sb.lastIndexOf(","));
		params += "}";

		String requestUrl = super.getGateUrl();
		this.setDebugInfo(this.getDebugInfo() + "\r\n" + "requestUrl:"
				+ requestUrl);
		TenpayHttpClient httpClient = new TenpayHttpClient();
		httpClient.setReqContent(requestUrl);
		String resContent = "";
		this.setDebugInfo(this.getDebugInfo() + "\r\n" + "post data:" + params);
        Log.getInstance().debug("fuck 000:" + requestUrl + "params:" + params);
		if (httpClient.callHttpPost(requestUrl, params)) {
			resContent = httpClient.getResContent();
            Log.getInstance().debug("prepayid accpet:" + resContent);
			if (2 == resContent.indexOf("prepayid")) {
				prepayid = JsonUtil.getJsonValue(resContent, "prepayid");
			}
			this.setDebugInfo(this.getDebugInfo() + "\r\n" + "resContent:"
					+ resContent);
		}
        Log.getInstance().debug("prepayid end:");
		return prepayid;
	}

	// 判断access_token是否失效
	public String sendAccessToken() {
		String accesstoken = "";
		StringBuffer sb = new StringBuffer("{");
		Set es = super.getAllParameters().entrySet();
		Iterator it = es.iterator();
		while (it.hasNext()) {
			Map.Entry entry = (Map.Entry) it.next();
			String k = (String) entry.getKey();
			String v = (String) entry.getValue();
			if (null != v && !"".equals(v) && !"appkey".equals(k)) {
				sb.append("\"" + k + "\":\"" + v + "\",");
			}
		}
		String params = sb.substring(0, sb.lastIndexOf(","));
		params += "}";

		String requestUrl = super.getGateUrl();
//		this.setDebugInfo(this.getDebugInfo() + "\r\n" + "requestUrl:"
//				+ requestUrl);
		TenpayHttpClient httpClient = new TenpayHttpClient();
		httpClient.setReqContent(requestUrl);
		String resContent = "";
//		this.setDebugInfo(this.getDebugInfo() + "\r\n" + "post data:" + params);
		if (httpClient.callHttpPost(requestUrl, params)) {
			resContent = httpClient.getResContent();
			if (2 == resContent.indexOf(ConstantUtil.ERRORCODE)) {
				accesstoken = resContent.substring(11, 16);//获取对应的errcode的值
			}
		}
		return accesstoken;
	}
}
