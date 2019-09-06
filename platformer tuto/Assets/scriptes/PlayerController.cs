using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

	
	private float mv_h = 0;
	bool jump = false;
	public float speed;
	public float rotationSpeed;
	Transform tfWeapon;
	Vector2 mousePosition;
	Vector2 lookDirection;
	// Use this for initialization
	void Start () {
		tfWeapon = gameObject.transform.Find("Weapon");
	}
	
	// Update is called once per frame
	void Update () {
		mv_h = Input.GetAxisRaw("Horizontal");
		if (Input.GetKeyDown(KeyCode.W))
			jump = true;
		mousePosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
		// Debug.Log(mv_h);
	}
	void FixedUpdate()
	{
		if (jump)
			GetComponent<Rigidbody2D>().AddForce(new Vector2(0, 8), ForceMode2D.Impulse);
		jump = false;
		lookDirection = (mousePosition - new Vector2(transform.position.x, transform.position.y)).normalized;
		if (tfWeapon != null)
		{
			tfWeapon.transform.up = lookDirection;
		}
		else
			Debug.Log("not found");
		transform.position = transform.position + new Vector3(mv_h, 0, 0) * speed * Time.fixedDeltaTime;
	}
}
