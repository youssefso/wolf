using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Camera : MonoBehaviour {

	// Use this for initialization
	private Vector3 pos;
	void Start () {
		pos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
	}
	
	// Update is called once per frame
	void Update () {
		Vector3 vec = pos - transform.position;
		float mag = vec.magnitude;
		Camera.main.transform.position = transform.position + mag * vec.normalized;
	}
}
